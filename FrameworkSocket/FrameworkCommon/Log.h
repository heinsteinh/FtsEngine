#pragma once
#include "TSingleton.h"

namespace Framework
{

	class CLog : public CSingleton<CLog>
	{

		typedef  std::unique_lock<std::mutex> scope_lock;

		friend class CSingleton<CLog>;

	public:
		CLog();
		virtual	~CLog();

		void	LogDebug(const char*, const char*, ...);
		void	LogMessage(const char*, const char*, ...);
		void	LogError(const char*, const char*, ...);


		bool startLog(std::string strPrefix, std::string strLogDir = "");
		bool closeLog();
		

	private:
		void	WriteToLog(const char*);

		uint32_t	m_LogCount;
		FILE*			m_pLogFile;

		std::mutex		m_lockWrite;

	};
}
