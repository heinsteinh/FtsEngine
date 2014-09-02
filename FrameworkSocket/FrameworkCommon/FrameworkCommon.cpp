// FrameworkCommon.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Compack.h"
#include "Log.h"


int _tmain(int argc, _TCHAR* argv[])
{

	try
	{

		Framework::CLog::GetInstance().startLog("Fts", "This");
		Framework::CLog::GetInstance().LogMessage("Main", "Log Test");
		Framework::CLog::GetInstance().LogError("Temps", "Log Test");
		Framework::CLog::GetInstance().LogDebug("Weezy", "Log Test");
		Framework::CLog::GetInstance().LogMessage("Service", "Log Test");
		getchar();
	}
	catch (...)
	{
		std::cout << "default exception";
	}

	return 0;
}

