#pragma once
#include "eventbridge.h"
#include <list>
#include <memory>
#include <mutex>
#include <atomic>


namespace core
{


	class EventChannel; //forward definition

	template <typename tEvent>
	class EventHandlerQueue {
	private: //the entire class is private, so no object may use it
		friend class EventChannel; //except for the EventChannel

		typedef EventHandler<tEvent> EventHandlerType;
		typedef std::shared_ptr<EventHandlerType> EventHandlerPtr; 
		typedef std::list<EventHandlerPtr> HandlerList;
		typedef typename HandlerList::iterator HandlerIterator;
		typedef typename HandlerList::const_iterator ConstHandlerIterator;

		typedef std::mutex Mutex;
		typedef std::unique_lock<Mutex> ScopedLock;
		
		HandlerList mHandlerList;
		HandlerList mSyncList;

		Mutex mHandlerMutex;
		std::atomic<bool> mBroadcasting;
		
		
		
		static EventHandlerQueue& instance() {
			static EventHandlerQueue anInstance;
			return anInstance;
		}

		template <class tHandler>
		void add(tHandler& handler) {
			mHandlerList.push_back(
				EventHandlerPtr(new EventBridge<tEvent, tHandler>(handler))
				);
		}

		void broadcast(const tEvent& object) {
			ConstHandlerIterator next;
			for (ConstHandlerIterator it = mHandlerList.begin(); it != mHandlerList.end();) {
				//the handle function might invalidate the iterator, so make a copy and advance immediately
				next = it++;
				(*next)->handle(object);
			}
		}
		

		//comparison predicate class (for removing handlers)
		template <class tHandler>
		class PointsToSame {
		public:
			typedef EventBridge<tEvent, tHandler> BridgeType;

			const tHandler& mHandler;

			PointsToSame(const tHandler& h) : mHandler(h) {}

			bool operator()(EventHandlerPtr ptr) {
				return ((*std::static_pointer_cast<BridgeType>(ptr)) == mHandler);
			}
		};

		template <class tHandler>
		void remove(const tHandler& handler) {
			PointsToSame<tHandler> pts(handler);
			mHandlerList.remove_if(pts);
		}



		template <typename tHandler>
		void add_safe(tHandler& handler) 
		{
			//assert(handler != nullptr);

			ScopedLock lock(mHandlerMutex);
			if (mBroadcasting)
				mSyncList.emplace_back(std::unique_ptr<EventBridge<tEvent, tHandler> >(new EventBridge<tEvent, tHandler>(handler)));
			else
				mHandlerList.emplace_back(std::unique_ptr<EventBridge<tEvent, tHandler> >(new EventBridge<tEvent, tHandler>(handler)));
		}


		void broadcast_safe(const tEvent& evt) {
			//thread-safe, starting block
			{
				ScopedLock lock(mHandlerMutex);
				mBroadcasting = true;
			}
			//handle events
			for (auto& handler : mHandlerList)
			{
				(*handler).handle(evt);
			}
				


			//thread-safe, closing block
			{
				ScopedLock lock(mHandlerMutex);
				mBroadcasting = false;
				std::move(mSyncList.begin(), mSyncList.end(), std::back_inserter(mHandlerList));
				mSyncList.clear();
			}
		}

		template <typename tHandler>
		void remove_safe(tHandler* handler) {
			ScopedLock lock(mHandlerMutex);

			for (auto& it = mHandlerList.cbegin(); it != mHandlerList.cend(); ++it) {
				auto ptr = dynamic_cast<Bridge<tEvent, tHandler>*>(it->get());
				if (ptr) {
					if (*ptr == handler) {
						mHandlerList.erase(it);
						break;
					}
				}
			}

			for (auto& it = mSyncList.cbegin(); it != mSyncList.cend(); ++it) {
				auto ptr = dynamic_cast<Bridge<tEvent, tHandler>*>(it->get());
				if (ptr) {
					if (*ptr == handler) {
						mSyncList.erase(it);
						break;
					}
				}
			}
		}

	};
}