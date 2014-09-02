// FrameworkSocket.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include "Log.h"

int _tmain(int argc, _TCHAR* argv[])
{
	try
	{
		Framework::CLog::GetInstance().LogMessage("Main", "Log Test");
		getchar();
	}
	catch (...) 
	{ 
		std::cout << "default exception"; 
	}


	

	return 0;
}

