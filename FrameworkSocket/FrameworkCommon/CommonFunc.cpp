
#include "CommonFunc.h"


#define  MAX_PATH_LEN 256

#include <thread>

uint32_t CommonFunc::GetProcessorNum()
{
	uint32_t dwNum = 0;
#ifdef _WIN64
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	dwNum = sysInfo.dwNumberOfProcessors * 2;
#else
	dwNum = sysconf(_SC_NPROCESSORS_CONF);
#endif
	return dwNum;
}


std::string CommonFunc::GetCurrentDir()
{
	char szPath[MAX_PATH_LEN];
#ifdef _WIN64
	_getcwd(szPath, MAX_PATH_LEN);
#else
	getcwd(szPath, MAX_PATH_LEN);
#endif
	return std::string(szPath);
}


uint32_t CommonFunc::GetTime()
{
	time_t t;
	t = time(0);
	return (uint32_t)t;
}

uint32_t CommonFunc::GetTickCount()
{
    uint32_t dwTickCount = 0;;
    
#ifdef _WIN64
	dwTickCount = ::GetTickCount();
    
#else
    /*
     struct timespec on;
     if (0 == clock_gettime(CLOCK_MONOTONIC, &on))
     {
     dwTickCount = on.tv_sec * 1000 + on.tv_nsec / 1000000;
     }*/
#endif
    return dwTickCount;
}

uint64_t CommonFunc::GetTickCount64()
{
#if WINVER < 0x0501
	return GetTickCount();
#else
    
#ifdef _WIN64
	return ::GetTickCount64();
#else
	UINT64 dwTickCount = 0;;
	struct timespec on;
	if (0 == clock_gettime(CLOCK_MONOTONIC, &on))
	{
		dwTickCount = on.tv_sec * 1000 + on.tv_nsec / 1000000;
	}
	return dwTickCount;
#endif
    
#endif
}


bool CommonFunc::CreateDir(std::string &strDir)
{
	int nRet = 0;
#ifdef _WIN64
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

uint32_t CommonFunc::GetCurThreadID()
{
	uint32_t dwThreadID = 0;
#ifdef _WIN64
	dwThreadID = ::GetCurrentThreadId();
#else
    
    //    static_assert(sizeof(std::thread::id)==sizeof(uint64_t),"this function only works if size of thead::id is equal to the size of uint_64");
    //    auto id=std::this_thread::get_id();
    //    uint64_t* ptr=(uint64_t*) &id;
    //    dwThreadID = (*ptr);
    
    
	//dwThreadID = (uint32_t)std::this_thread::get_id().hash(); //(UINT32)pthread_self();
#endif
	return dwThreadID;
}


uint32_t CommonFunc::GetFreePhysMemory()
{
	uint32_t dwFreeSize = 0;
#ifdef _WIN64
	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof (statex);
	GlobalMemoryStatusEx(&statex);
	dwFreeSize = (uint32_t)(statex.ullAvailPhys / 1024 / 1024);
#else
	uint32_t dwPageSize;
	uint32_t dwFreePages = 0;
	dwPageSize = sysconf(_SC_PAGESIZE) / 1024;
	//dwFreePages = sysconf(_SC_AVPHYS_PAGES) / 1024;
	dwFreeSize = dwFreePages * dwPageSize;
#endif
    
	return dwFreeSize;
}
