#pragma once


namespace core
{

	template <class> class EventHandlerQueue; //forward definition

	template <class tEvent>
	class EventHandler {
	private:
		friend class EventHandlerQueue<tEvent>;

		virtual void handle(const tEvent& object) = 0;
	};
}