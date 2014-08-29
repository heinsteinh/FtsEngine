#pragma once



#include <cstdint>

namespace wmdf
{

	class BaseEvent
	{
	public:
		BaseEvent(void);
		virtual ~BaseEvent(void);
		int32_t event_id(){ return event_id_; }
		void set_event_id(int32_t event_id){ event_id_ = event_id; }
	private:
		int32_t event_id_;
	};
}
