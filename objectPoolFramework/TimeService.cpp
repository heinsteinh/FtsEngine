#include "stdafx.h"
#include "TimeService.h"



#if defined(_WIN32)
#pragma warning ( disable : 4786 ) 
#pragma warning ( disable : 4996 ) 
#pragma warning ( disable : 4345 ) 
#include <WinSock2.h>
#include <Windows.h>
#include <crtdbg.h>
#include <MSWSock.h>
#pragma comment ( lib, "winmm.lib" )
#pragma comment(lib,"ws2_32.lib")
#endif

namespace tin
{

	void TimeService::InitTimeService()
	{
#if defined(_WIN32)
		m_StartTime = timeGetTime();
		m_CurrentTime = timeGetTime();
#endif
	}
	int TimeService::Delay()
	{
		uint32_t oldTime = m_CurrentTime;
#if defined(_WIN32)
		uint32_t curTime = timeGetTime();
#endif
		if (curTime - oldTime < m_Interval)
			return (m_Interval - (curTime - oldTime));
		return 0;
	}

	uint32_t TimeService::Tick()
	{
#if defined(_WIN32)
		m_CurrentTime = timeGetTime();
#endif
		return m_CurrentTime;
	}
}