
#include "Log.h"


#include "Log.h"
#include "StringFormat.h"
#include "Compack.h"


#define TRUE 1
#define FALSE 0

using namespace Framework;


std::string GetCurrentDir()
{
	
#define  MAX_PATH_LEN 256

	char szPath[MAX_PATH_LEN];

#ifdef WIN32
	_getcwd(szPath, MAX_PATH_LEN);
#else
	getcwd(szPath, MAX_PATH_LEN);

#endif

	return std::string(szPath);
}





bool CreateDir(std::string &strDir)
{
	int nRet = 0;
#ifdef WIN32
	nRet = _mkdir(strDir.c_str());
#else
	nRet = mkdir(strDir.c_str(), S_IRWXU);
#endif

	if (nRet == 0)
	{
		return true;
	}
	if (errno == EEXIST)
	{
		return true;
	}
	return false;
}



CLog::CLog()
{
#ifdef __unix__
	openlog("ffxivd", LOG_PID | LOG_NDELAY, LOG_USER);
#endif

	

	
}

CLog::~CLog()
{
#ifdef __unix__
	closelog();
#endif

	closeLog();
}


bool CLog::closeLog()
{

	if (m_pLogFile == NULL)
	{
		return false;
	}

	fflush(m_pLogFile);
	fclose(m_pLogFile);

	m_pLogFile = NULL;

	return TRUE;
}


bool CLog::startLog(std::string strPrefix, std::string strLogDir)
{

	std::string strPath = GetCurrentDir();
	strPath += ("/Log");

	if (!CreateDir(strPath))
	{
		return FALSE;
	}

	m_pLogFile = NULL;
	time_t _time;
	time(&_time);
	tm *pTime = localtime(&_time);
	
	char szFileName[256];
	sprintf(szFileName, "%s/%s-%02d%02d%02d-%02d%02d%02d.log", strPath.c_str(), strPrefix.c_str(), pTime->tm_year, pTime->tm_mon, pTime->tm_mday, pTime->tm_hour, pTime->tm_min, pTime->tm_sec);
	m_pLogFile = fopen(szFileName, "w+");
	if (m_pLogFile == NULL)
	{
		return false;
	}
	m_LogCount = 0;
	

	return true;
}






void CLog::LogDebug(const char* serviceName, const char* format, ...)
{

	if (m_pLogFile == NULL)
	{
		return;
	}


	char buf[512];
	memset(buf, 0, sizeof(0));

	time_t now = time(NULL);
	struct tm *ts = localtime(&now);
	
	time_t _time;
	time(&_time);
	tm *pTime = localtime(&_time);	
	sprintf(buf, "[%02d-%02d-%02d %02d:%02d:%02d] ", pTime->tm_year % 100, pTime->tm_mon, pTime->tm_mday, pTime->tm_hour, pTime->tm_min, pTime->tm_sec);
	

#ifdef _DEBUG
	va_list args;
	va_start(args, format);
	auto body = string_format(format, args);
	va_end(args);
	auto message = string_format("%s [Debug] %s: %s", buf, serviceName, body.c_str());
	WriteToLog(message.c_str());


	strcat((char*)message.c_str(), "\n");
	scope_lock lck(m_lockWrite);
	{
		fputs(message.c_str(), m_pLogFile);
		m_LogCount++;
		if (m_LogCount >= 1)
		{
			fflush(m_pLogFile);
			m_LogCount = 0;
		}
	}
#endif



}

void CLog::LogMessage(const char* serviceName, const char* format, ...)
{

	if (m_pLogFile == NULL)
	{
		return;
	}


	char buf[512];
	memset(buf, 0, sizeof(0));

	time_t now = time(NULL);
	struct tm *ts = localtime(&now);

	time_t _time;
	time(&_time);
	tm *pTime = localtime(&_time);
	sprintf(buf, "[%02d-%02d-%02d %02d:%02d:%02d] ", pTime->tm_year % 100, pTime->tm_mon, pTime->tm_mday, pTime->tm_hour, pTime->tm_min, pTime->tm_sec);



	va_list args;
	va_start(args, format);
	auto body = string_format(format, args);
	va_end(args);
	auto message = string_format("%s [Info ] %s: %s", buf, serviceName, body.c_str());
	WriteToLog(message.c_str());

	
	strcat((char*)message.c_str(), "\n");
	scope_lock lck(m_lockWrite);
	{
		fputs(message.c_str(), m_pLogFile);
		m_LogCount++;
		if (m_LogCount >= 1)
		{
			fflush(m_pLogFile);
			m_LogCount = 0;
		}
	}

}


void CLog::LogWarnning(const char* serviceName, const char* format, ...)
{

	if (m_pLogFile == NULL)
	{
		return;
	}

	char buf[512];
	memset(buf, 0, sizeof(0));

	time_t now = time(NULL);
	struct tm *ts = localtime(&now);

	time_t _time;
	time(&_time);
	tm *pTime = localtime(&_time);
	sprintf(buf, "[%02d-%02d-%02d %02d:%02d:%02d] ", pTime->tm_year % 100, pTime->tm_mon, pTime->tm_mday, pTime->tm_hour, pTime->tm_min, pTime->tm_sec);


	va_list args;
	va_start(args, format);
	auto body = string_format(format, args);
	va_end(args);
	auto message = string_format("%s [Warn ] %s: %s", buf, serviceName, body.c_str());
	WriteToLog(message.c_str());


	strcat((char*)message.c_str(), "\n");
	scope_lock lck(m_lockWrite);
	{
		fputs(message.c_str(), m_pLogFile);
		m_LogCount++;
		if (m_LogCount >= 1)
		{
			fflush(m_pLogFile);
			m_LogCount = 0;
		}
	}

}



void CLog::LogError(const char* serviceName, const char* format, ...)
{

	if (m_pLogFile == NULL)
	{
		return;
	}

	char buf[512];
	memset(buf, 0, sizeof(0));

	time_t now = time(NULL);
	struct tm *ts = localtime(&now);

	time_t _time;
	time(&_time);
	tm *pTime = localtime(&_time);
	//sprintf(buf, "[%02d-%02d-%02d %02d:%02d:%02d][%08x]  ", pTime->tm_year % 100, pTime->tm_mon, pTime->tm_mday, pTime->tm_hour, pTime->tm_min, pTime->tm_sec, 0xffffffff & (uint32_t)std::this_thread::get_id().hash());
	sprintf(buf, "[%02d-%02d-%02d %02d:%02d:%02d]  ", pTime->tm_year % 100, pTime->tm_mon, pTime->tm_mday, pTime->tm_hour, pTime->tm_min, pTime->tm_sec);

	va_list args;
	va_start(args, format);
	auto body = string_format(format, args);
	va_end(args);
	auto message = string_format("%s [Error] %s: %s", buf, serviceName, body.c_str());
	WriteToLog(message.c_str());


	strcat((char*)message.c_str(), "\n");
	scope_lock lck(m_lockWrite);
	{
		fputs(message.c_str(), m_pLogFile);
		m_LogCount++;
		if (m_LogCount >= 1)
		{
			fflush(m_pLogFile);
			m_LogCount = 0;
		}
	}

}





void CLog::WriteToLog(const char* message)
{
#ifdef __unix__
	syslog(LOG_NOTICE, "%s", message);
#else
	puts(message);
#endif
}


