// FrameworkCommon.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Compack.h"
#include "Log.h"


#include "Streaming.h"
#include "CommonMessage.h"


int _tmain(int argc, _TCHAR* argv[])
{

	try
	{

		Framework::CLog::GetInstance().startLog("Fts", "This");
		Framework::CLog::GetInstance().LogMessage("Main", "Log Test");
		Framework::CLog::GetInstance().LogError("Temps", "Log Test");
		Framework::CLog::GetInstance().LogDebug("Weezy", "Log Test");
		Framework::CLog::GetInstance().LogMessage("Service", "Log Test");


		Framework::GameCreateMessage gmeMsg;
		gmeMsg.gridSize = 2;
		gmeMsg.numPlayers = 3;
		gmeMsg.timeout = 3;
		gmeMsg.gridSize = 5;
		gmeMsg.numPlanes = 6;
		gmeMsg.headshots = 1;
		gmeMsg.reveal = 1;
		gmeMsg.gamePassword = "test";




		
		

		getchar();
	}
	catch (...)
	{
		std::cout << "default exception";
	}

	return 0;
}

