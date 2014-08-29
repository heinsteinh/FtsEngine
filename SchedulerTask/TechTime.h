///////////////////////////////////////////////////////////////////////////////
// $Id$

#ifndef INCLUDED_TECHTIME_H
#define INCLUDED_TECHTIME_H

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <mmsystem.h>
#include <limits.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif


#ifdef _MSC_VER
#pragma once
#endif

///////////////////////////////////////////////////////////////////////////////

#pragma comment(lib, "winmm.lib")

namespace TechTime
{

	class MyClass
	{
	public:
		static double TimeGetSecs();

	private:

	};

	


#if defined(_MSC_VER)
	inline INT64 ReadTSC()
	{
		INT64 t;
		unsigned int a, b;
		unsigned int * c = (unsigned int *)&t;
		__asm
		{
			_emit 0x0f;
			_emit 0x31;
			mov a, eax;
			mov b, edx;
		}
		c[0] = a;
		c[1] = b;
		return t;
	}
#elif defined(__GNUC__)
	inline int64 ReadTSC()
	{
		int64 t;
		asm(".byte 0x0f,0x31" // opcode 0x0F31
			:"=A" (t)          // output parameters : edx:eax -> t
			:                  // no input register
			: "%eax", "%edx");  // registers destroyed in asm
		return t;
	}
#else
#error ("Need inline assembly for reading timestamp counter")
#endif

	///////////////////////////////////////////////////////////////////////////////

}
#endif // !INCLUDED_TECHTIME_H