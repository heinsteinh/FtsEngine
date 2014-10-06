
#ifndef __COMMON_FUNCTION__
#define __COMMON_FUNCTION__




#include "Compack.h"


#define MAX_PATH_LEN 256


namespace CommonFunc
{
	uint32_t	GetProcessorNum();
	std::string	GetCurrentDir();
    
	bool		CreateDir(std::string &strDir);
	
	uint32_t	GetTime();
	uint32_t	GetTickCount();
	uint64_t	GetTickCount64();
	uint32_t	GetCurThreadID();
	uint32_t	GetFreePhysMemory();
}
#endif /* __COMMON_FUNCTION__*/