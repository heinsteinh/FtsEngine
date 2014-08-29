#pragma once

#ifndef _Logger_H_
#define _Logger_H_

#include "LoggerInterface.h"
#include "TSingleton.h"

#include <list>
#include <mutex>

namespace tin
{
	class LoggerInterface;
	class LoggingSystem : public CSingleton<LoggingSystem>
	{
		friend class CSingleton<LoggingSystem>;

	public:

		static void LogMessage(const char *format, ...);
		static void LogWarning(const char *format, ...);
		static void LogError(const char *format, ...);

		void AddInterface(LoggerInterface *interface);
		void RemoveInterface(LoggerInterface *interface);

		~LoggingSystem();
		LoggingSystem();

	private:
		void Init();
		void Shutdown();


		void LogMessageInternal(const char *message);
		void LogWarningInternal(const char *message);
		void LogErrorInternal(const char *message);

		std::list<LoggerInterface *> interfaces_;

		std::mutex logging_mutex_;
		friend class Singleton;
	};
} // tin

#endif