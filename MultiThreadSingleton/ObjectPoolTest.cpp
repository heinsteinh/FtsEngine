#include "stdafx.h"
#include "ObjectPoolTest.h"

#include "TimeService.h"
#include "ObjectPool.h"
#include <list>


using namespace XServer;

void ObjectPoolTest()
{
	TimeService t2;
	t2.InitTimeService();
	for (int i = 0; i < 1000000; i++)
	{
		TimeService* pObj = new TimeService();
		delete pObj;
	}
	t2.Tick();
	std::cout << "New 1 time : " << t2.RunTime() << std::endl;

	TimeService t1;
	t1.InitTimeService();
	for (int i = 0; i < 1000000; i++)
	{
		TimeService* pObj = ObjectPool<TimeService>::GetInstance().Pop();
		ObjectPool<TimeService>::GetInstance().Push(pObj);
	}
	t1.Tick();
	std::cout << "Pool 1 time : " << t1.RunTime() << std::endl;

	TimeService t3;
	t3.InitTimeService();
	for (int i = 0; i < 1000000; i++)
	{
		TimeService* pObj = ObjectPool<TimeService>::GetInstance().Pop();
		ObjectPool<TimeService>::GetInstance().Push(pObj);
	}
	t3.Tick();
	std::cout << "Pool 2 time : " << t3.RunTime() << std::endl;

	TimeService t4;
	t4.InitTimeService();
	for (int i = 0; i < 1000000; i++)
	{
		TimeService* pObj = new TimeService();
		delete pObj;
	}
	t4.Tick();
	std::cout << "New 2 time : " << t4.RunTime() << std::endl;
}


void MemAllocTest()
{
	int nSize = 0;

	TimeService t1;
	t1.InitTimeService();
	for (int i = 0; i < 10000000; i++)
	{
		nSize = RandLimits(4, 512);
		void* p = MemAllocT.Alloc(nSize);
		MemAllocT.Dealloc(p, nSize);
	}
	t1.Tick();
	std::cout << "Pool 1 time : " << t1.RunTime() << std::endl;

	TimeService t2;
	t2.InitTimeService();
	for (int i = 0; i < 10000000; i++)
	{
		nSize = RandLimits(4, 512);
		char* p = new char[nSize];
		delete[] p;
	}
	t2.Tick();
	std::cout << "New 1 time : " << t2.RunTime() << std::endl;

	TimeService t3;
	t3.InitTimeService();
	for (int i = 0; i < 10000000; i++)
	{
		nSize = RandLimits(4, 512);
		void* p = MemAllocT.Alloc(nSize);
		MemAllocT.Dealloc(p, nSize);
	}
	t3.Tick();
	std::cout << "Pool 2 time : " << t3.RunTime() << std::endl;

	TimeService t4;
	t4.InitTimeService();
	for (int i = 0; i < 10000000; i++)
	{
		nSize = RandLimits(4, 512);
		char* p = new char[nSize];
		delete[] p;
	}
	t4.Tick();
	std::cout << "New 2 time : " << t4.RunTime() << std::endl;
}


void TestFunction()
{
	// remember our allocs
	std::list<void*> _allocs;
	size_t allocSize = 64;

	TimeService* pObj = ObjectPool<TimeService>::GetInstance().Pop();
	ObjectPool<TimeService>::GetInstance().Push(pObj);

	// lots of iterations
	for (int i = 0; i < MAX_MEMORY_PAGE; i++)
	{
		// allocate blocks till the allocator is full
		for (int i = 0; i < MAX_MEMORY_PAGE; i++)
		{

			void* alloc = MemAllocT.Alloc(allocSize);  // s_pAllocator.allocate(allocSize,__FILE__, __LINE__);

			if (!alloc)
				break;

			_allocs.push_back(alloc);
		}


		// randomly mark ~50% of blocks to remove
		std::list<void*> allocsToRemove;
		for (std::list<void*>::iterator it = _allocs.begin(); it != _allocs.end(); it++)
		{
			if ((rand() % 2) == 0)
			{
				allocsToRemove.push_back(*it);
			}
		}

		// deallocate the blocks
		for (std::list<void*>::iterator it = allocsToRemove.begin(); it != allocsToRemove.end(); it++)
		{
			MemAllocT.Dealloc(*it, allocSize);
			_allocs.remove(*it);
		}
	}


	// cleanup before exitting
	for (std::list<void*>::iterator it = _allocs.begin(); it != _allocs.end(); it++)
	{
		MemAllocT.Dealloc(*it, allocSize);
	}




	//mem_free(pVertex);

}
