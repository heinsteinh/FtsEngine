#include "stdafx.h"
#include "LoggerEx.h"



namespace Logger
{
	Event g_events[BUFFER_SIZE];
	LONG g_pos = -1;
}