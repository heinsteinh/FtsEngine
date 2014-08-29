#pragma once


#ifndef PE_UTILS_LOG_HPP
#define PE_UTILS_LOG_HPP

//#include <common.hpp>

#include <thread>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <thread>
#include <iostream>
#include <vector>
#include <mutex>

#include <chrono>
#include <ctime>
#include <iostream>


#include <iomanip>
#include <ctime>
#include <chrono>

namespace pe
{
	namespace utils
	{
		class Log
		{
			enum LogSeverity
			{
				LL_FATAL,
				LL_ERROR,
				LL_WARN,
				LL_INFO,
				LL_DEBUG
			};

		public:
			static Log& getInstance();

			~Log();

			void logINFO(std::string message);
			void logWARN(std::string message);
			void logERROR(std::string message);
			void logERRORSDL(std::string message);
			void logFATAL(std::string message);
			void logDEBUG(std::string message);

			void setLogLevel(LogSeverity level);
			int getLogLevel();

		private:
			Log();
			Log(const Log& cc);

			std::tm* Log::getTimeStamp();

			int loggingLevel;
		};
	}
}

#endif