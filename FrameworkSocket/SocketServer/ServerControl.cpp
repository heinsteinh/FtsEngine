#include "stdafx.h"
#include "ServerControl.h"


#include "../FrameworkCommon/Compack.h"
#include "../FrameworkCommon/Log.h"
#include "../FrameworkCommon/CommonSocket.h"


#include <cassert>
#include <functional>

#define LOG_NAME ("ServerHandler")

using namespace Framework;


ServerControl::ServerControl(std::string address, int port) :m_address(address), m_iPort(port)
{

}

ServerControl::~ServerControl()
{
}

void ServerControl::Start()
{

	ServerThreadProc();
}


void ServerControl::ServerThreadProc()
{
	SOCKET m_clientlistnerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	{
		int reuseOptionValue = 1;
		int result = setsockopt(m_clientlistnerSocket, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char*>(&reuseOptionValue), sizeof(reuseOptionValue));
		assert(result == 0);
	}



	sockaddr_in service;
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr("127.0.0.1");
	service.sin_port = htons(55555);

	if (bind(m_clientlistnerSocket, reinterpret_cast<sockaddr*>(&service), sizeof(sockaddr_in)))
	{
		CLog::GetInstance().LogError(LOG_NAME, "Failed to bind socket.");
		return;
	}

	if (listen(m_clientlistnerSocket, SOMAXCONN))
	{
		CLog::GetInstance().LogError(LOG_NAME, "Failed to listen on socket.");
		return;
	}

	CLog::GetInstance().LogMessage(LOG_NAME, "Game server started.");

	while (1)
	{
		sockaddr_in incomingAddr;
		socklen_t incomingAddrSize = sizeof(sockaddr_in);
		SOCKET incomingSocket = accept(m_clientlistnerSocket, reinterpret_cast<sockaddr*>(&incomingAddr), &incomingAddrSize);

		CLog::GetInstance().LogMessage(LOG_NAME, "Accept Client : %s:%d\n", inet_ntoa(incomingAddr.sin_addr), ntohs(incomingAddr.sin_port));

		/*PlayerConnectionHandler* connectionHandler = new PlayerConnectionHandler(incomingSocket, incomingAddr);
		connectionHandler->Start();*/
	}

	Net::CloseSocket(m_clientlistnerSocket);
}


