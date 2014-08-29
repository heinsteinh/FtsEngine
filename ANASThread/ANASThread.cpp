// ANASThread.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"

#include "Logger.h"
#include "debug.h"


#include "BridgeParameter.h"

#include <fstream>
#include <iostream>
#include <deque>

using namespace std;

inline void EnableMemLeakCheck()
{
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
}

int _tmain(int argc, _TCHAR* argv[])
{
	EnableMemLeakCheck();

	runApp::android_main(NULL, NULL, 1);

	abort();

	return 0;
}


