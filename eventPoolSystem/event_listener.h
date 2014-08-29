#pragma once

namespace wmdf
{
	class BaseEvent;
	class EventListener
	{
	public:
		EventListener(void);
		virtual ~EventListener(void);
		virtual void HandleEvent(BaseEvent* feed_event) = 0;
	};
}

