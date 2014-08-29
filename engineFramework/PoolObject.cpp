#include "stdafx.h"
#include "PoolObject.h"



namespace entityx
{

	BasePool::~BasePool() 
	{
		for (char *ptr : blocks_)
		{
			delete[] ptr;
		}
	}

} // namespace entityx