// MemoryMaster.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define MM_USE_GENERAL_MEMORY_POOL


#define YON_DEPRECATED __declspec(deprecated)
#define YON_COMPILE_WITH_WIN32

#if defined(YON_COMPILE_WITH_WIN32)&&defined(_DEBUG)&&!defined(_AFX)||defined(ENFORCE_CHECK_MEMORY)
#include <crtdbg.h>
#define YON_CHECK_MEMORY
#define YON_ORIGIN_NEW new
#define YON_DEBUG_NEW new(_CLIENT_BLOCK, __FILE__, __LINE__)
#endif



#include "MemoryMaster.h"

using namespace mm;


//ÄÚ´æÐ¹Â©¼ì²â











class Base {
	int a, b;
	float c, d;
};

class Test : public Base {
public:
	Test() {}
	~Test() {}
};

class TestAppendMemoryPool :public Base, public mm::Poolable<Test, 10000>
{
public:
	TestAppendMemoryPool() {}
	~TestAppendMemoryPool() {}
};


int _tmain(int argc, _TCHAR* argv[])
{


	{
		//boost::progress_timer t;
		Test* ptr;
		for (int j = 0; j < 100; ++j)
		{
			for (int i = 0; i < 100; ++i)
			{
				ptr = new Test;
				delete ptr;
			}
		}

	}

	{

	//boost::progress_timer t;
	TestAppendMemoryPool::Init();
	TestAppendMemoryPool* ptr;
	for (int j = 0; j < 10000; ++j)
	{
		for (int i = 0; i < 10000; ++i)
		{
			ptr = new TestAppendMemoryPool;
			delete ptr;
		}
	}
}

	//boost::progress_timer t;
	mm::PoolableFactory<Test, 10000> mp;
	Test* ptr;
	for (int j = 0; j < 10000; ++j)
	{
		for (int i = 0; i < 10000; ++i)
		{
			ptr = mp.New();
			mp.Delete(ptr);
		}
	}


	return 0;
}

