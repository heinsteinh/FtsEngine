
#ifndef _LoggerInterface_H_
#define _LoggerInterface_H_



#include <set>
#include <vector>
#include <string>
#include <thread>
#include <functional>
#include <stdio.h>
#include <stdarg.h>


#define Bit(X)(1 << X)
typedef int LoggerOption;

typedef enum{
	ALL = Bit(0),
	ERROR = Bit(1),
	WARNING = Bit(2),
	MESSAGE = Bit(3),
	VERBOSE = Bit(4)
} LoggerOptions;

namespace tin{
	class LoggerInterface {
	public:
		LoggerInterface() { };
		virtual ~LoggerInterface() { };

		virtual void LogMessage(const char *message) = 0;
		virtual void LogWarning(const char *message) = 0;
		virtual void LogError(const char *message) = 0;

		virtual LoggerOption RespondsToOptions() = 0;
	};
} // tin
#endif