#pragma once

#include <vector>
#include <list>
#include <mutex>
#include <thread>


namespace wmdf
{
	class EventListener;
	class BaseEvent;

	class EventPool
	{
	public:
		EventPool(void);
		virtual ~EventPool(void);
		void AddEvent(BaseEvent* feed_event);
		void RegisterListener(EventListener* listener);
		void UnRegisterListener(EventListener* listener);

		void UnRegisterAllListener();
		void BeginListen();
		void EndListen();
		bool IsMonitoring();

	protected:
		void ProcessEvent();

	private:
		std::vector<EventListener*> listeners_;
		std::list<BaseEvent*> events_;
		std::vector<BaseEvent*> event_copies_;
		std::mutex listener_mutex_;
		std::mutex event_mutex_;
		std::thread* work_thread_;
	
		volatile bool isworking_;
	};
}


