#pragma once

#include <time.h>
#include <string>
#include <stdio.h>
#include <stdarg.h>
#include <cstdarg>
#include <cstdio>
#include <algorithm>    // std::swap
#include <iostream>
#include <strstream>
#include <sstream>

namespace BubbleBattleBoids
{

	static inline void Logger_app(const char *moduleName, const char *loglevel, const std::string message, ...)
	{
		time_t now = time(NULL);
		struct tm *ts = localtime(&now);
		printf("[%s] - [%04d-%02d-%02d %02d:%02d:%02d] [%s] ",
			moduleName,
			ts->tm_year + 1900,
			ts->tm_mon + 1,
			ts->tm_mday,
			ts->tm_hour,
			ts->tm_min,
			ts->tm_sec,
			loglevel
			);

		va_list args;
		va_start(args, message);
		vprintf(message.c_str(), args);
		va_end(args);

		printf("\n");
	}


	typedef struct _vec2
	{
		int x;
		int y;
	} vec2;

	// vector stuff
	static inline std::string Inspect(const std::string& str) {
		return str;
	}

	static inline std::string Inspect(const vec2& v) 
	{
		std::stringstream ss;
		ss << "{x:" << v.x << ", y:" << v.y << "}";
		return ss.str();
	}
}



#define LOG_INFO(format, ...)  BubbleBattleBoids::Logger_app("eventFramework", "INFO: ", format, ##__VA_ARGS__)
#define LOG_WARN(format, ...)  BubbleBattleBoids::Logger_app("eventFramework", "WARN: ", format, ##__VA_ARGS__)
#define LOG_ERROR(format, ...) BubbleBattleBoids::Logger_app("eventFramework", "ERROR:", format, ##__VA_ARGS__)
#define LOG_ERROR(format, ...) BubbleBattleBoids::Logger_app("eventFramework", "ERROR:", format, ##__VA_ARGS__)

#define FTS_INSPECT(obj) BubbleBattleBoids::Inspect(obj).c_str()



	