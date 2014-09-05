#include "stdafx.h"

#include "MyServer.h"
#include "TaskClient.h"

#include "../FrameworkCommon/TaskQueue.h"
#include "../FrameworkCommon/Log.h"


using namespace Framework;

#define LOG_NAME "MyServer"

MyServer::MyServer(const std::string& address, const int port, int iThreadCount) :Framework::ThreadPooledServer(address, port, iThreadCount)
{

}


MyServer::~MyServer()
{
}



void MyServer::Run()
{

	if (OpenServerSocket())
	{
		TaskSocket* pTaskSocket;

		while (!IsStopped())
		{
			SOCKET clientSocket = -1;

			sockaddr_in incomingAddr;
			socklen_t incomingAddrSize = sizeof(sockaddr_in);
			SOCKET incomingSocket = accept(m_ServerSocket, reinterpret_cast<sockaddr*>(&incomingAddr), &incomingAddrSize);

			CLog::GetInstance().LogMessage(LOG_NAME, "Accept Client : %s:%d\n", inet_ntoa(incomingAddr.sin_addr), ntohs(incomingAddr.sin_port));

			pTaskSocket = (new TaskSocket(incomingSocket, incomingAddr)); // will be automaitcall delete when done
			
			m_pPool->Post(pTaskSocket);

		}
	}	
}


