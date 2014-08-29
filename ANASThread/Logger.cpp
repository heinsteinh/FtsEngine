#include "stdafx.h"
#include "Logger.h"




#include <time.h>
#include <windows.h> 


#include <vector>
#include <cassert>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <cstdio>
#include <cstdarg>




namespace fts
{

	static std::vector<ConsumerCallback>gConsumers;
	static std::vector<OnConsumeHandler>gConsumers_;  // test



	LogEntry::Type LogEntry::General = 0;

	namespace Log {

		static bool active = false;
		static bool useTimestamp = false;

		void init()
		{
			printf("%s\n", __FILE__);
			printf("%s\n", __LINE__);


			assert(active == false);
			//assert(active == false, "Log::init should only be called once.");

			// Set up general init values.
			active = true;
		}

		//--------------------------------------

		void shutdown()
		{
			assert(active == true);
			//assert(active == true, "Log::shutdown should only be called once.");
			active = false;
		}



		static void _printf(LogEntry::Level level, LogEntry::Type type, const char* fmt, va_list argptr)
		{

			if (!active)
				return;
			Log::active = false;

			char buffer[1024];
			U32 offset = 0;

			memset(buffer, 0, 1024);

#ifdef _MSC_VER
			//vsnprintf_s(buffer, sizeof buffer, fmt, argptr);
#else
			vsnprintf(buffer, sizeof buffer, format, args);
#endif	

			
			LogEntry entry;
			entry.mData = fmt;
			entry.mLevel = level;
			entry.mType = type;

			for (U32 i = 0; i < gConsumers.size(); i++)
				gConsumers[i](level, &entry);

				
			Log::active = true;

		}




		//------------------------------------------------------------------------------
		void printf(const char* fmt, ...)
		{
			va_list argptr;
			va_start(argptr, fmt);
			_printf(LogEntry::Normal, LogEntry::General, fmt, argptr);
			va_end(argptr);
		}

		void warnf(LogEntry::Type type, const char* fmt, ...)
		{
			va_list argptr;
			va_start(argptr, fmt);
			_printf(LogEntry::Warning, type, fmt, argptr);
			va_end(argptr);
		}

		void errorf(LogEntry::Type type, const char* fmt, ...)
		{
			va_list argptr;
			va_start(argptr, fmt);
			_printf(LogEntry::Error, type, fmt, argptr);
			va_end(argptr);
		}

		void warnf(const char* fmt, ...)
		{
			va_list argptr;
			va_start(argptr, fmt);
			_printf(LogEntry::Warning, LogEntry::General, fmt, argptr);
			va_end(argptr);
		}

		void errorf(const char* fmt, ...)
		{
			va_list argptr;
			va_start(argptr, fmt);
			_printf(LogEntry::Error, LogEntry::General, fmt, argptr);
			va_end(argptr);
		}


		//---------------------------------------------------------------------------
		void addConsumer(ConsumerCallback consumer)
		{
			gConsumers.push_back(consumer);
		}


		void removeConsumer(ConsumerCallback consumer)
		{
			auto result1 = std::find(std::begin(gConsumers), std::end(gConsumers), consumer); // iterator position
			if (result1 != std::end(gConsumers))
			{
				std::cout << "v contains: " << '\n';
				gConsumers.erase(result1);
			}
			else {
				std::cout << "v does not contain: " << '\n';
			}
		}
	}

	void OnAppLog2(U32 level, fts::LogEntry *logEntry)
	{
		switch (logEntry->mLevel)
		{
		case  fts::LogEntry::Normal:
			fprintf(stdout, "%s\n", logEntry->mData);
			break;
		case  fts::LogEntry::Warning:
			fprintf(stdout, "%s\n", logEntry->mData);
			break;
		case  fts::LogEntry::Error:
			fprintf(stderr, "%s\n", logEntry->mData);
			break;
		default:
			break;
		}
	}

	void OnAppLog(U32 level, fts::LogEntry *logEntry)
	{
		switch (logEntry->mLevel)
		{
		case  fts::LogEntry::Normal:
			printf( "Info: %s\n", logEntry->mData);
			break;
		case  fts::LogEntry::Warning:
			printf( "Warn: %s\n", logEntry->mData);
			break;
		case  fts::LogEntry::Error:
			printf("Error: %s\n", logEntry->mData); 
			break;
		default:
			break;
		}
	}


}
