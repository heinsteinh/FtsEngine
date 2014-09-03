// SocketServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include "ServerControl.h"

int _tmain(int argc, _TCHAR* argv[])
{

	ServerControl server("127.0.0.1", 55555);
	server.Start();

	return 0;
}

