#pragma once



// ============================================================================
// Platform-specific information goes in this header file.  
//
// GDK Defines the following macros for platform specific code:
//
// GDKPLATFORM_WINDOWS          : Microsoft Windows (2000, XP, Vista, 7, etc)
//
// GDKPLATFORM_APPLE            : Apple
//   GDKPLATFORM_MACOSX         : Apple \ Mac OS X
//   GDKPLATFORM_IOS            : Apple \ iOS
//
// TODO:
//   GDKPLATFORM_LINUX              : Linux OS
//   GDKPLATFORM_NACL           : Google NaCl
//   GDKPLATFORM_ANDROID        : Android phones
//
// Wiiware, 3dsware, etc
// ============================================================================

//----------------------------------------------------------------------------
// Platform:  Microsoft Windows
//----------------------------------------------------------------------------
#ifdef WIN32

#define GDKPLATFORM_WINDOWS

// Common Types
// ----------------

typedef __int8  Int8;
typedef __int16 Int16;
typedef __int32 Int32;
typedef __int64 Int64;
typedef unsigned __int8         UInt8;
typedef unsigned __int16        UInt16;
typedef unsigned __int32        UInt32;
typedef unsigned __int64        UInt64;

typedef UInt8   Byte;
typedef UInt16  Word;
typedef UInt32  DWord;

// Windows headers
#include <windows.h>



#endif



// ---------------------------------------------------------------------------
// Common Types

typedef UInt8   Byte;
typedef UInt16  Word;
typedef UInt32  DWord;

// ---------------------------------------------------------------------------
// Standard Includes

// C++ headers
#include <cassert>
#include <cctype>
#include <cfloat>
#include <climits>
#include <cmath>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <fstream>

// STL headers
#include <utility>
#include <string>
#include <algorithm>
#include <vector>
#include <list>
#include <map>
#include <stack>
#include <queue>
#include <deque>
#include <set>

#include <mutex>
#include <condition_variable>
#include <memory>
#include <thread>

using namespace std;


// ---------------------------------------
// GDK Macros

#define GDK_NOT_USED(x) ((void)(x))


