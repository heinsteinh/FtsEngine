#include "stdafx.h"
#include "Log.h"

#pragma warning(disable : 4996)

using namespace pe::utils;

Log& Log::getInstance()
{
	static Log instance;
	return instance;
}

Log::~Log()
{}

Log::Log()
: loggingLevel(4)
{}

void Log::logFATAL(std::string message)
{
	std::cout << std::put_time((std::tm*)getTimeStamp(), "%c") << " [FATAL] " << message.c_str() << std::endl;
}

void Log::logERROR(std::string message)
{
	if (LL_ERROR <= loggingLevel)
		std::cout << std::put_time((std::tm*)getTimeStamp(), "%c") << " [ERROR] " << message.c_str() << std::endl;
}

void Log::logERRORSDL(std::string message)
{
	//if (LL_ERROR <= loggingLevel)
	//	std::cout << std::put_time((std::tm*)getTimeStamp(), "%c") << " [ERROR] " << message.c_str() << ": " << SDL_GetError() << std::endl;
}

void Log::logWARN(std::string message)
{
	if (LL_WARN <= loggingLevel)
		std::cout << std::put_time((std::tm*)getTimeStamp(), "%c") << " [WARN] " << message.c_str() << std::endl;
}

void Log::logINFO(std::string message)
{
	if (LL_INFO <= loggingLevel)
		std::cout << std::put_time((std::tm*)getTimeStamp(), "%c") << " [INFO] " << message.c_str() << std::endl;
}

void Log::logDEBUG(std::string message)
{
	if (LL_DEBUG <= loggingLevel)
		std::cout << std::put_time((std::tm*)getTimeStamp(), "%c") << " [DEBUG] " << message.c_str() << std::endl;
}

void Log::setLogLevel(LogSeverity level)
{
	loggingLevel = (int)level;
}

int Log::getLogLevel()
{
	return loggingLevel;
}


std::tm* Log::getTimeStamp()
{
	

	using std::chrono::system_clock;
	std::time_t tt = system_clock::to_time_t(system_clock::now());
	std::tm* ptm = std::localtime(&tt);
	return ptm;

	/*
	const auto now = std::chrono::system_clock::now();
	const auto time = std::chrono::system_clock::to_time_t(now);
	std::cout << std::ctime(&time);*/
}
