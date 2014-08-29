

#pragma once 
#include <cassert>
#include <memory>
#include <mutex>
#include <vector>




namespace h4d {

	template <typename T>
	struct EventHandler {
		virtual void operator()(const T& value) = 0;
	};


	class  EventChannel 
	{
	private:

		template <typename tEvent, typename tHandler>
		struct Bridge : public EventHandler<tEvent> {
			tHandler& mHandler;
			Bridge(tHandler& handler) : mHandler(handler) {}
			void operator()(const tEvent& value) { (mHandler)(value); }
			bool operator == (const tHandler& handler) const { return mHandler == handler; }
		};
		

		


		template <typename tEvent>
		struct EventHandlerQueue {
			typedef EventHandler<tEvent> EventHandlerType;
			typedef std::unique_ptr<EventHandlerType> EventHandlerPtr;
			typedef std::vector<EventHandlerPtr> HandlerList;
			typedef std::mutex Mutex;
			typedef std::lock_guard<Mutex> ScopedLock;

			Mutex mHandlerMutex;
			bool mBroadcasting;
			HandlerList mHandlers;
			HandlerList mSyncList;

			EventHandlerQueue() : mBroadcasting(false) {}

			static EventHandlerQueue& instance() {
				static EventHandlerQueue evQueue;
				return evQueue;
			}

			template <typename tHandler>
			void add(tHandler& handler) {
				//assert(handler != nullptr);

				ScopedLock lock(mHandlerMutex);
				if (mBroadcasting)
					mSyncList.emplace_back(std::unique_ptr<Bridge<tEvent, tHandler> >(new Bridge<tEvent, tHandler>(handler)));
				else
					mHandlers.emplace_back(std::unique_ptr<Bridge<tEvent, tHandler> >(new Bridge<tEvent, tHandler>(handler)));
			}

			template <typename tHandler>
			void remove(tHandler* handler) {
				ScopedLock lock(mHandlerMutex);

				for (auto& it = mHandlers.cbegin(); it != mHandlers.cend(); ++it) {
					auto ptr = dynamic_cast<Bridge<tEvent, tHandler>*>(it->get());
					if (ptr) {
						if (*ptr == handler) {
							mHandlers.erase(it);
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

			void broadcast(const tEvent& evt) {
				//thread-safe, starting block
				{
					ScopedLock lock(mHandlerMutex);
					mBroadcasting = true;
				}
				//handle events
				for (auto& handler : mHandlers)
					(*handler)(evt);
				//thread-safe, closing block
				{
					ScopedLock lock(mHandlerMutex);
					mBroadcasting = false;
					std::move(mSyncList.begin(), mSyncList.end(), std::back_inserter(mHandlers));
					mSyncList.clear();
				}
			}
		};

		template <typename tEventType, class tHandler>
		class EventBridge : public EventHandler<tEventType> 
		{
		private:
			friend struct EventHandlerQueue<tEventType>;

			tHandler& mHandler;

			EventBridge(tHandler& handler);
						
			void handleEvent(const tEventType& value);

		public:
			bool operator == (const tHandler& handler) const;
		};




	public:
		template <typename tEvent, class tHandler>
		void add(tHandler& handler) {
			EventHandlerQueue<tEvent>::instance().add(handler);
		}

		template <typename tEvent, class tHandler>
		void remove(tHandler* handler) {
			EventHandlerQueue<tEvent>::instance().remove(handler);
		}

		template <typename tEvent>
		void broadcast(const tEvent& evt) {
			EventHandlerQueue<tEvent>::instance().broadcast(evt);
		}
	};


	//Implementation
	template <typename T, class U>
	EventChannel::EventBridge<T, U>::EventBridge(U& handler) :
		mHandler(handler)
	{
	}

	template <typename T, class U>
	void EventChannel::EventBridge<T, U>::handleEvent(const T& object) {
		mHandler.handle(object);
	}

	template <typename T, class U>
	bool EventChannel::EventBridge<T, U>::operator == (const U& handler) const {
		return ((&mHandler) == (&handler));
	}


}