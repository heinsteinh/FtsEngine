#include "stdafx.h"
#include "Memory.h"
#include "Assert.h"

#include <cstring>


using namespace Gdk;

#ifdef GDK_MEMORY_TRACKING

// Static instantiations
Memory::MemoryMap* Memory::memoryMap = NULL;
Memory::AllocatorFunc Memory::allocatorFunc = &Memory::CAllocator;
Memory::DeallocatorFunc Memory::deallocatorFunc = &Memory::CDeallocator;
unsigned int Memory::MemoryEntry::uniqueIdCounter = 0;


// ********************************************************
void Memory::Init()
{

	// Setup the default allocator & de-allocator methods
	allocatorFunc = &CAllocator;
	deallocatorFunc = &CDeallocator;

	// Create the memory map
	memoryMap = new MemoryMap();
}


std::string GetExeFileName()
{
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, (LPWSTR)buffer, MAX_PATH);
	return std::string(buffer);
}

std::string GetExePath()
{
	std::string f = GetExeFileName();
	return f.substr(0, f.find_last_of("\\/"));
}

// ********************************************************
void Memory::Shutdown()
{
	// Assert that the map should exist
	ASSERT(memoryMap != NULL, L"Memory::Shutdown called and the memoryMap is NULL");

	// Log all the unfreed memory chunks
	// ---------------------------------

	// Get a path to the memory dump file
	string workingFolder = ""; // = Path::GetCommonPath(CommonPaths::WorkingFolder);
	string dumpFilePath  = ""; // Path::Combine(workingFolder, string("GdkMemory.dump"));



	// Open the memory dump file

	/*FILE* outFile = fopen(dumpFilePath.c_str(), "wt");
	if (!outFile)
		return;*/

	
	{
		char buffer[MAX_PATH];
		HMODULE module = GetModuleHandle(L"engineFrameworkMemory.exe");
		GetModuleFileNameA(module, buffer, MAX_PATH);
		string::size_type pos = string(buffer).find_last_of("\\/");
		workingFolder = string(buffer).substr(0, pos);
	}

	dumpFilePath = workingFolder + string("/GdkMemory.dump");

	FILE* outFile = NULL;
	errno_t error_;
	error_ = fopen_s(&outFile, dumpFilePath.c_str(), "wt");
	
	if (error_!=0)
		return;

	fprintf(outFile, "Unfreed Allocations:\r\n");

	// Create a sorted map from the memory map based on unique ID.
	SortedMap sorted;
	MemoryMap::const_iterator mapIter = memoryMap->begin();
	MemoryMap::const_iterator mapEnd = memoryMap->end();
	for (/**/; mapIter != mapEnd; ++mapIter)
	{
		sorted[mapIter->second.uniqueId] =
			std::make_pair(mapIter->first, mapIter->second);
	}

	// Write the sorted map to disk.
	SortedMap::const_iterator sortedIter = sorted.begin();
	SortedMap::const_iterator sortedEnd = sorted.end();
	for (/**/; sortedIter != sortedEnd; ++sortedIter)
	{
		unsigned int uniqueID = sortedIter->first;
		void* address = sortedIter->second.first;
		MemoryEntry entry = sortedIter->second.second;

		fprintf(outFile, "Address[%p] Size[%8d] Dims[%1d] - File[%s] Line[%d]\r\n",
			address, entry.numBytes, entry.numDimensions, entry.file, entry.line
			);
	}

	// Close the dump file
	fclose(outFile);

	// Delete the map
	delete memoryMap;
	memoryMap = NULL;
}

// ********************************************************
void* Memory::CreateBlock(size_t numBytes, int numDimensions) const
{

	// Allocate the block
	void* memBlock = allocatorFunc(numBytes, this->file, this->line);

	// Create an entry in the memory map for this allocation
	(*memoryMap)[memBlock] = MemoryEntry(numBytes, numDimensions, this->file, this->line);

	return memBlock;
}

// ********************************************************
void* Memory::Alloc(size_t numBytes)
{
	std::lock_guard<std::mutex> lock(memLock);
	return CreateBlock(numBytes, 0);
}

// ********************************************************
void Memory::Free(void* ptr)
{	
	std::lock_guard<std::mutex> lock(memLock);
	{
		if (ptr == NULL)
			return;

		MemoryMap::iterator iter = memoryMap->find(ptr);
		if (iter != memoryMap->end())
		{
			if (iter->second.numDimensions == 0)
			{
				// Remove ptr from memory map.
				memoryMap->erase(ptr);
				deallocatorFunc(ptr, this->file, this->line);
			}
			else
			{
				ASSERT(false, L"Mismatch in dimensions.\n");
			}
		}
		else
		{
			ASSERT(false, L"Memory block not in map.\n");
		}
	}
}

// ********************************************************
void* Memory::CAllocator(size_t numBytes, const char*, int)
{
	return malloc(numBytes);
}

// ********************************************************
void Memory::CDeallocator(void* memBlock, const char*, int)
{
	free(memBlock);
}

#else // GDK_MEMORY_TRACKING

void Memory::Init()
{
}

void Memory::Shutdown()
{
}

#endif // GDK_MEMORY_TRACKING
