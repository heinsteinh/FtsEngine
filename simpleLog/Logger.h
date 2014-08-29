#pragma  once 

#include <string>


#include <time.h>
#include <string>
#include <stdio.h>
#include <stdarg.h>
#include <cstdarg>
#include <cstdio>

#include <iostream>
#include <strstream>
#include <sstream>

#include <stdlib.h>

static const char* BLACK = "\e[1;30m";
static const char* RED = "\e[1;31m";
static const char* GREEN = "\e[1;32m";
static const char* YELLOW = "\e[1;33m";
static const char* BLUE = "\e[1;34m";
static const char* MAGENTA = "\e[1;35m";
static const char* CYAN = "\e[1;36m";
static const char* WHITE = "\e[1;37m";
static const char* ANSI_RESET = "\e[0m";




static inline void PrintColor(const char* prefix, const char* pStr, ...)
{
	va_list a;
	va_start(a, pStr);
	int bytes = 1 + vsnprintf(0, 0, pStr, a);
	char* msg = (char*)malloc(bytes);
	va_start(a, pStr);
	vsnprintf(msg, bytes, pStr, a);
	fputs(prefix, stdout);
	fputs(msg, stdout);
	puts(ANSI_RESET);
	free(msg);
}


static inline void Logger_app(const char *moduleName, const char *loglevel, char* message, ...)
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
	int len;
	char * buffer;

	va_start(args, message);
	len = _vscprintf(message, args) // _vscprintf doesn't count
		+ 1; // terminating '\0'
	buffer = (char*)malloc(len * sizeof(char));
	vsprintf_s(buffer, len, message, args);
	puts(buffer);
	free(buffer);


	printf("\n");

	va_list ArgPtr;
	static char FinalString[2048];
	va_start(ArgPtr, message);
	vsprintf_s(FinalString, sizeof(FinalString), message, ArgPtr);
	va_end(ArgPtr);
	
	printf("[%s]", FinalString);

	printf("\n");
	
}



#define LOG_INFO(format, ...)  Logger_app("WeezyApp", "INFO: ", format, ##__VA_ARGS__)
#define LOG_WARN(format, ...)  Logger_app("WeezyApp", "WARN: ", format, ##__VA_ARGS__)
#define LOG_ERROR(format, ...) Logger_app("WeezyApp", "ERROR:", format, ##__VA_ARGS__)
#define LOG_ERROR(format, ...) Logger_app("WeezyApp", "ERROR:", format, ##__VA_ARGS__)
