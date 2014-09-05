#pragma once


#include "../FrameworkCommon/ThreadPooledServer.h"


class MyServer : public Framework::ThreadPooledServer
{
public:
	MyServer(const std::string& address, const int port, int iThreadCount);
	~MyServer();

	void Run() override;
	
	
};

