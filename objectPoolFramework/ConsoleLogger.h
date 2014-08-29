#pragma once


#include "LoggerInterface.h"

namespace tin {
	class ConsoleLogger :public LoggerInterface 
	{
	public:
		ConsoleLogger();
		~ConsoleLogger();

		virtual void LogMessage(const char *message);
		virtual void LogWarning(const char *message);
		virtual void LogError(const char *message);

		virtual LoggerOption RespondsToOptions();
	};

}