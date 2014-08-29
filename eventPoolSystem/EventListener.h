#pragma once

//https://github.com/yxdtiger/Test/blob/d6fdf95bfccb4c0fea40d79c14eeca608fa9a6c9/Test/Src/V10/Src/monitor/event_listener.h

namespace core
{

	template <class> 
	class EventHandlerQueue; //forward definition

	template <class tEvent>
	class EventListener {

		EventListener();
		~EventListener();

	private:
		friend class EventHandlerQueue<tEvent>;
		virtual void onEvent(const tEvent& object) = 0;
	};
}