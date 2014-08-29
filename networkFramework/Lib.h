#ifndef _COMPACT_H_
#define _COMPACT_H_

#if defined(_WIN32)
#pragma warning ( disable : 4786 ) 
#pragma warning ( disable : 4996 ) 
#pragma warning ( disable : 4345 ) 
#include <WinSock2.h>
#include <Windows.h>
#include <crtdbg.h>
#include <MSWSock.h>
#pragma comment ( lib, "winmm.lib" )
#pragma comment(lib,"ws2_32.lib")
#endif

#include <stdio.h>
#include <iostream>
#include <time.h>
#include <math.h>
#include <stdarg.h>
#include <memory.h>
#include <assert.h>

#include <vector>
#include <list>
#include <map>
#include <set>
#include <algorithm>

#include <functional>




typedef unsigned char	UCHAR;
typedef char	CHAR;
typedef unsigned int	UINT;
typedef int	INT;
typedef unsigned short	USHORT;
typedef short	SHORT;
typedef unsigned long	ULONG;
typedef long	LONG;
typedef float	FLOAT;
typedef unsigned long long ULONGLONG;

typedef UCHAR	uchar;
typedef USHORT	ushort;
typedef UINT	uint;
typedef ULONG	ulong;
typedef INT	BOOL;
typedef UCHAR	BYTE;
typedef ULONGLONG ulonglong;

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef VOID
#define VOID void
#endif

#endif