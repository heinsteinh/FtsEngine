#include "stdafx.h"
#include "ConsoleLogger.h"


#include <iostream>

namespace tin {
	ConsoleLogger::~ConsoleLogger(){

	}

	ConsoleLogger::ConsoleLogger(){

	}

	void ConsoleLogger::LogMessage(const char *message) {
		std::cout << "M: " << message << std::endl;
	}

	void ConsoleLogger::LogWarning(const char *message) {
		std::cout << "W: " << message << std::endl;
	}

	void ConsoleLogger::LogError(const char *message) {
		std::cout << "E: " << message << std::endl;
	}

	LoggerOption ConsoleLogger::RespondsToOptions() {
		return ALL;
	}
}



