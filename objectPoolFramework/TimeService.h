#pragma once

#include <stdint.h>

namespace tin
{
	
	class TimeService
	{
	public:
		TimeService(const int interval = 0)
			: m_Interval(interval)
			, m_StartTime(0)
			, m_CurrentTime(0)
		{}
		~TimeService(){};

		
		void InitTimeService();
		uint32_t CurrentTime() const { return m_CurrentTime; }
		uint32_t StarUpTime() const { return m_StartTime; }
		uint32_t RunTime() const { return (m_CurrentTime - m_StartTime); }
		
		uint32_t Tick();
		
		int Delay();
	private:
		uint32_t m_Interval;
		uint32_t m_StartTime;
		uint32_t m_CurrentTime;
	};
}