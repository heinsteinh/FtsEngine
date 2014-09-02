#pragma once
#include "TSingleton.h"

namespace Framework
{

	class CLog : public CSingleton<CLog>
	{

		friend class CSingleton<CLog>;

	public:
		CLog();
		virtual	~CLog();

		void	LogDebug(const char*, const char*, ...);
		void	LogMessage(const char*, const char*, ...);
		void	LogError(const char*, const char*, ...);

	private:
		void	WriteToLog(const char*);
	};
}
