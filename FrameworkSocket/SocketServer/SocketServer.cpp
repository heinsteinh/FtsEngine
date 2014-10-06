// SocketServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include "MyServer.h"
#include "../FrameworkCommon/ThreadBase.h"
#include "../FrameworkCommon/Log.h"

#include "ServerControl.h"

int _tmain(int argc, CHAR* argv[])
{

	Framework::CLog::GetInstance().startLog("Srv", "AppDir");

	std::shared_ptr<MyServer> server(new MyServer("127.0.0.1", 55555));
	Framework::Thread ServerThread(server.get());
	//Framework::Thread* ServerThread= new Framework::Thread(server.get());


	std::this_thread::sleep_for(std::chrono::seconds(15));


	return 0;
}

