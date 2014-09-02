#include "stdafx.h"
#include "Log.h"


#include "Log.h"
#include "StringFormat.h"


using namespace Framework;


CLog::CLog()
{
#ifdef __unix__
	openlog("ffxivd", LOG_PID | LOG_NDELAY, LOG_USER);
#endif
}

CLog::~CLog()
{
#ifdef __unix__
	closelog();
#endif
}
void CLog::LogDebug(const char* serviceName, const char* format, ...)
{

	wchar_t buf[100];
	time_t now = time(NULL);
	struct tm *ts = localtime(&now);

	int len = swprintf(buf, 100, L"[%04d-%02d-%02d %02d:%02d:%02d]", ts->tm_year + 1900,
		ts->tm_mon + 1,
		ts->tm_mday,
		ts->tm_hour,
		ts->tm_min,
		ts->tm_sec);


	printf("[%s]  ", buf);


		

#ifdef _DEBUG
	va_list args;
	va_start(args, format);
	auto body = string_format(format, args);
	va_end(args);
	auto message = string_format("%s [D] %s: %s", buf, serviceName, body.c_str());
	WriteToLog(message.c_str());
#endif
}
void CLog::LogMessage(const char* serviceName, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	auto body = string_format(format, args);
	va_end(args);
	auto message = string_format("[M] %s: %s", serviceName, body.c_str());
	WriteToLog(message.c_str());
}
void CLog::LogError(const char* serviceName, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	auto body = string_format(format, args);
	va_end(args);
	auto message = string_format("[E] %s: %s", serviceName, body.c_str());
	WriteToLog(message.c_str());
}
void CLog::WriteToLog(const char* message)
{
#ifdef __unix__
	syslog(LOG_NOTICE, "%s", message);
#else
	puts(message);
#endif
}