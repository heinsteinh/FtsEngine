// engineFrameworkMemory.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define GDK_MEMORY_TRACKING

#include "Memory.h"


class Foo
{
public:
	Foo::Foo()
	{
		printf("Ctor... \n");
	}

	Foo::~Foo()
	{
		printf("Dtor... \n");
	}
};




int _tmain(int argc, _TCHAR* argv[])
{
	
	// Init the GDK Memory
	Gdk::Memory::Init();

	Foo *foo = GdkNew Foo();
	GdkDelete<Foo>(foo);


	//    1D Array of created objects
	Foo *foo1D = GdkNew1DArray<Foo>(10);
	GdkDelete1DArray<Foo>(foo1D);

	////    2D Array of created objects
	Foo **foo2D = GdkNew2DArray<Foo>(10, 20);
	GdkDelete2DArray<Foo>(foo2D);

	//     malloc & free
	Byte* buffer = (Byte*)GdkAlloc(100);
	GdkFree(buffer);


	Gdk::Memory::Shutdown();
	return 0;
}

