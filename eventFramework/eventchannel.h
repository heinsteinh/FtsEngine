#pragma once
#include "eventhandlerqueue.h"


namespace core
{


	class EventChannel 
	{
	public:
		template <typename tEvent, class tHandler>
		void add(tHandler& handler)
		{
			EventHandlerQueue<tEvent>::instance().add_safe<tHandler>(handler);
		}

		template <typename tEvent, class tHandler>
		void remove(const tHandler& handler) {
			EventHandlerQueue<tEvent>::instance().remove_safe<tHandler>(handler);
		}

		template <typename tEvent>
		void broadcast(const tEvent& object) {
			EventHandlerQueue<tEvent>::instance().broadcast_safe(object);
		}
	};

}