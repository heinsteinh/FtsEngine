#include "stdafx.h"
#include "LoggingSystem.h"




#define MAX_PRINT_MESSAGE_SIZE 4096

namespace tin {


	LoggingSystem::LoggingSystem(){

	}

	LoggingSystem::~LoggingSystem(){
		std::list<LoggerInterface *>::iterator iter;
		for (iter = interfaces_.begin(); iter != interfaces_.end(); ++iter){
			LoggerInterface *interface = *iter;
			delete interface;
			iter = interfaces_.erase(iter);
		}
		interfaces_.clear();
	}

	void LoggingSystem::Init(){

	}

	void LoggingSystem::Shutdown(){

	}

	void LoggingSystem::LogMessage(const char *format, ...){
		va_list args;
		va_start(args, format);
		char message[MAX_PRINT_MESSAGE_SIZE];
		vsnprintf(message, MAX_PRINT_MESSAGE_SIZE, format, args);
		va_end(args);
		LoggingSystem::GetInstance().LogMessageInternal(message);
	}

	void LoggingSystem::LogWarning(const char *format, ...){
		va_list args;
		va_start(args, format);
		char message[MAX_PRINT_MESSAGE_SIZE];
		vsnprintf(message, MAX_PRINT_MESSAGE_SIZE, format, args);
		va_end(args);
		LoggingSystem::GetInstance().LogWarningInternal(message);
	}

	void LoggingSystem::LogError(const char *format, ...){
		va_list args;
		va_start(args, format);
		char message[MAX_PRINT_MESSAGE_SIZE];
		vsnprintf(message, MAX_PRINT_MESSAGE_SIZE, format, args);
		va_end(args);
		LoggingSystem::GetInstance().LogErrorInternal(message);
	}

	void LoggingSystem::LogMessageInternal(const char *message){
		std::list<LoggerInterface *>::iterator iter;
		for (iter = interfaces_.begin(); iter != interfaces_.end(); ++iter){
			LoggerInterface *interface = *iter;
			int options = interface->RespondsToOptions();
			if (options & ALL || options & MESSAGE){
				logging_mutex_.lock();
				interface->LogMessage(message);
				logging_mutex_.unlock();
			}
		}
	}

	void LoggingSystem::LogWarningInternal(const char *message){
		std::list<LoggerInterface *>::iterator iter;
		for (iter = interfaces_.begin(); iter != interfaces_.end(); ++iter){
			LoggerInterface *interface = *iter;
			int options = interface->RespondsToOptions();
			if (options & ALL || options & WARNING){
				logging_mutex_.lock();
				interface->LogWarning(message);
				logging_mutex_.unlock();
			}
		}
	}

	void LoggingSystem::LogErrorInternal(const char *message){
		std::list<LoggerInterface *>::iterator iter;
		for (iter = interfaces_.begin(); iter != interfaces_.end(); ++iter){
			LoggerInterface *interface = *iter;
			int options = interface->RespondsToOptions();
			if (options & ALL || options & ERROR){
				logging_mutex_.lock();
				interface->LogError(message);
				logging_mutex_.unlock();
			}
		}
	}

	void LoggingSystem::AddInterface(tin::LoggerInterface *interface){
		interfaces_.push_back(interface);
	}

	void LoggingSystem::RemoveInterface(LoggerInterface *interface){
		interfaces_.remove(interface);
	}
}