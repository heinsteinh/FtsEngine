
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

#include <cassert>
#include <cstdint>



#include <arpa/inet.h>
#include <errno.h>
#include <netinet/tcp.h>

#include <stddef.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include <sys/types.h> /* basic system data types */
#include <sys/socket.h> /* basic socket definitions */
#include <sys/time.h> /* timeval{} for select() */
#include <time.h> /* timespec{} for pselect() */
#include <netinet/in.h> /* sockaddr_in{} and other Internet defns */
#include <arpa/inet.h> /* inet(3) functions */
#include <errno.h>
#include <fcntl.h> /* for nonblocking */
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> /* for S_xxx file mode constants */



typedef char	INT8;
typedef unsigned char	UINT8;
typedef short	INT16;
typedef unsigned short UINT16;
typedef int	INT32;
typedef unsigned int	UINT32;
typedef int	BOOL;
typedef void	VOID;
typedef float	FLOAT;
typedef double	DOUBLE;
typedef long long INT64;
typedef unsigned long long UINT64;
typedef char	BYTE;
typedef char	CHAR;
typedef int	SOCKET;
typedef int	HANDLE;
#define INVALID_SOCKET (-1)
#define MAXEPOLLSIZE 10000


# if defined (WIN32)
typedef __int64 TimeStamp;
# elif defined (__linux__)
typedef __int64_t TimeStamp;
# elif defined (__APPLE__)
typedef __int64_t TimeStamp;
# endif