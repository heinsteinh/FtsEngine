#pragma once

#include "EventListenerQueue.h"
#include <queue>
#include <thread>

namespace Framework
{
	class IEventDispatcher;

	/// Implements event delivery system
	/** @ingroup Framework */
	class CEventServer
	{
	public:

		CEventServer(std::mutex& lock, std::condition_variable& evnt);

		~CEventServer();

		void Start() {  m_active = true; }

		void Stop() {  m_active = false; }

		bool isActive() { return m_active; }

		/// Sends notifications synchronously
		void SendEvent(CEventListenerQueue listeners, IEventDispatcher* dispatcher);

		/// Adds event to notification queue
		void PostEvent(const CEventListenerQueue& listeners, IEventDispatcher* dispatcher);

		/// Dispatches all scheduled events
		void DeliverEvents();

		/// Server has some events to be delivered
		bool HasPendingEvents() const;

	private:
			
		
		void DoSendEvent(const CEventListenerQueue& listeners, IEventDispatcher* dispatcher);

	private:
		/// \todo Add dispatcher pool
		typedef std::queue<std::pair<CEventListenerQueue, IEventDispatcher*> > TEventQueue;
		typedef std::unique_lock<std::mutex>  scoped_lock;

		TEventQueue m_queue;
		std::mutex& m_refFwkLock;
		std::condition_variable& m_refFwkEvent;
		bool m_active;
	};

} // namespace

