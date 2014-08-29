// ThreadPool.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <stdio.h>
#include <wtypes.h>
#include <stdarg.h>
#include <tchar.h>


#include <string>
#include <iostream>



#include "TraceFile.h"
#include "DelegateHeader.h"


//http://repository-of-projects.googlecode.com/svn/trunk/Win32/ThreadPool/main.cpp

#include <windows.h>
#include <list>
#include "Mutex.h"



#include "ThreadClass.h"
#include "ThreadPoolClass.h"


using namespace std;



const static unsigned int BUFFER_SIZE = 1024;
char m_buffer[BUFFER_SIZE];
void Log(const char* format, ...)
{
	va_list arg;
	va_start(arg, format);
	memset(m_buffer, 0x0, BUFFER_SIZE);
	vsprintf_s(m_buffer, BUFFER_SIZE, format, arg);
	printf("%s", m_buffer);
	va_end(arg);
}

#define WEEZY_DEBUG(format, ...) Log(format,##__VA_ARGS__)


inline void EnableMemLeakCheck()
{
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
}


namespace ThreadPoolSpace
{

	void TRACE(const char * pszFormat, ...)
	{
		va_list pArgs;
		char szMessageBuffer[16380] = { 0 };
		va_start(pArgs, pszFormat);
		vsnprintf_s(szMessageBuffer, 16380, 16380 - 1, pszFormat, pArgs);
		va_end(pArgs);
		OutputDebugStringA(szMessageBuffer);
	}

	

	struct SMyRunnable1 : public IRunnable
	{	

		virtual void run()
		{
			TRACE("start SMyRunnable1()\r\n");
			for (int i = 0; i < 100; ++i)
			{
				Sleep(100);
				TRACE("SMyRunnable1(%d)\r\n", i);
			}
			TRACE("end SMyRunnable1()\r\n");
		}
	};		
	
	
	int counter = 1;
	mutex mm;
	void test()
	{	mm.wait();
		counter <<= 1;
		counter -= 1;
		TRACE("test:%d\r\n", counter);
		mm.notify();
	}

}



using namespace ThreadPoolSpace;

int _tmain(int argc, _TCHAR* argv[])
{

	EnableMemLeakCheck();

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); // 获取标准输出设备句柄
	SetConsoleTitleA("Bank System"); // 获取窗口标题
	SetConsoleTextAttribute(hOut,FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE );
	//SetConsoleTextAttribute(hOut, BACKGROUND_GREEN);
	char fpath[_MAX_PATH];
	_fullpath(fpath, "./", _MAX_PATH);
	printf(fpath);
	TRACE("test\n");
	printf("\ntest\n");


	
	SMyRunnable1 r1;
	Thread t1(&r1);
	t1.start();
	TRACE("has start\r\n");
	

	delegate<void> d(test);
	ThreadPool<void> pool(10);
	pool.start();

	//for (int i = 0; i<10; ++i)
	//{
	//	getchar();
	//	pool.add(&d);
	//}
	//
	
	Log("%s\r\n", "helloworld");
	WEEZY_DEBUG("helloworld\r\n");
	WEEZY_DEBUG("%s\r\n", "helloworld");

	system("pause");

	return 0;
}

