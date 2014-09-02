// FrameworkSocket.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include "Log.h"

int _tmain(int argc, _TCHAR* argv[])
{

	Framework::CLog::GetInstance().LogMessage("Main", "Log Test");
	return 0;
}

