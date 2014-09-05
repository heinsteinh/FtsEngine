
#pragma once

#ifdef WIN32


#pragma warning ( disable : 4786 ) 
#pragma warning ( disable : 4996 ) 
#pragma warning ( disable : 4345 ) 

#include <Winsock2.h>
#include <Ws2tcpip.h>

#include <Windows.h>
#include <crtdbg.h>
#include <MSWSock.h>

#include <direct.h>
#include <stdlib.h>
#include <stdio.h>


#pragma comment ( lib, "winmm.lib" )
#pragma comment(lib,"ws2_32.lib")

#pragma comment(lib,"zdll.lib")

#else

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>


typedef int SOCKET;
#define SOCKET_ERROR (-1)

#endif



#include <stdio.h>
#include <iostream>
#include <time.h>
#include <math.h>
#include <stdarg.h>
#include <memory.h>
#include <assert.h>


#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <algorithm>
#include <functional>
#include <memory>
#include <vector>

#include <cassert>
#include <cstdint>


# if defined (WIN32)
typedef __int64 TimeStamp;
# elif defined (__linux__)
typedef __int64_t TimeStamp;
# endif