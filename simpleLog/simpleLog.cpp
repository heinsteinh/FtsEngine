// simpleLog.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <time.h>
#include <string>
#include <stdio.h>
#include <stdarg.h>
#include <cstdarg>
#include <cstdio>

#include <iostream>
#include <strstream>
#include <sstream>


#include "Logger.h"


#include "MemoryManager.h" 

#include "MemoryOperators.h"

//
//static inline void PrintColor(const char* prefix, const char* pStr, ...)
//{
//	va_list a;
//	va_start(a, pStr);
//	int bytes = 1 + vsnprintf(0, 0, pStr, a);
//	char* msg = (char*)malloc(bytes);
//	va_start(a, pStr);
//	vsnprintf(msg, bytes, pStr, a);
//	fputs(prefix, stdout);
//	fputs(msg, stdout);
//	puts(ANSI_RESET);
//	free(msg);
//}
//
//inline void Logger_app(const char *moduleName, const char *loglevel, const std::string message, ...)
//{
//	time_t now = time(NULL);
//	struct tm *ts = localtime(&now);
//	printf("[%s] - [%04d-%02d-%02d %02d:%02d:%02d] [%s] ",
//		moduleName,
//		ts->tm_year + 1900,
//		ts->tm_mon + 1,
//		ts->tm_mday,
//		ts->tm_hour,
//		ts->tm_min,
//		ts->tm_sec,
//		loglevel
//		);
//
//
//	PrintColor(GREEN, message.c_str());
//
//	va_list args;
//	va_start(args, message);
//	vprintf(message.c_str(), args);
//	va_end(args);
//
//	printf("\n");
//}


typedef struct _vec2
{
	int x;
	int y;
} vec2;

// vector stuff
static inline std::string Inspect(const std::string& str) {
	return str;
}

static inline std::string Inspect(const vec2& v) {
	std::stringstream ss;
	ss << "{x:" << v.x << ", y:" << v.y << "}";
	return ss.str();
}


//char* appName = "WeezyApp";
//#define LOG_INFO(format, ...)  Logger_app(appName, "INFO: ", format, ##__VA_ARGS__)
//#define LOG_WARN(format, ...)  Logger_app(appName, "WARN: ", format, ##__VA_ARGS__)
//#define LOG_ERROR(format, ...) Logger_app(appName, "ERROR:", format, ##__VA_ARGS__)
//#define LOG_ERROR(format, ...) Logger_app(appName, "ERROR:", format, ##__VA_ARGS__)

#define FTS_INSPECT(obj) Inspect(obj).c_str()

class a
{
public:
	a()
	{
	}

	~a()
	{
	}

private:

};


int _tmain(int argc, _TCHAR* argv[])
{
	a*  a_= new a;

	bool isThreading = false;

	//PrintColor(RED, "Evaluating %s L-System...",
	//	isThreading ? "multithreaded" : "single-threaded");

	//LOG_INFO("Une info",5, "Tesz");
	//LOG_WARN("Une Warn", 5, "Tesz");
	//LOG_ERROR("Une Erreur", 5, "Tesz");

	vec2 v; 
	v.x = 0;
	v.y = 0;

	//LOG_INFO(FTS_INSPECT(v));

	delete a_;
	
	SanityCheck();

	return 0;
}

