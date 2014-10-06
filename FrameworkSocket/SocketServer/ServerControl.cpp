#include "stdafx.h"
#include "ServerControl.h"


#include "../FrameworkCommon/Compack.h"
#include "../FrameworkCommon/Log.h"
#include "../FrameworkCommon/CommonSocket.h"
#include "../FrameworkCommon/BlockSocket.h"
#include "../FrameworkCommon/Exceptions.h"



#include "TaskClient.h"

#include <cassert>
#include <functional>

#define LOG_NAME ("ServerControl")

using namespace Framework;







ServerControl::ServerControl(std::string address, int port) :m_address(address), m_iPort(port)
{
	quit_flag = false;
}

ServerControl::~ServerControl()
{
	quit_flag = true;
}

void ServerControl::Start()
{

	ServerThreadProc();
}


void ServerControl::ServerThreadProc()
{
	Net::InitNetwork();


	SOCKET m_clientlistnerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	{
		int reuseOptionValue = 1;
		int result = setsockopt(m_clientlistnerSocket, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char*>(&reuseOptionValue), sizeof(reuseOptionValue));
		assert(result == 0);
	}

	Net::SetSocketNoDelay(m_clientlistnerSocket);
	Net::SetSocketReuseable(m_clientlistnerSocket);
	Net::SetSocketBlock(m_clientlistnerSocket);


	sockaddr_in service;
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr("127.0.0.1");
	service.sin_port = htons(55555);

	if (bind(m_clientlistnerSocket, reinterpret_cast<sockaddr*>(&service), sizeof(sockaddr_in)) == INVALID_SOCKET)
	{
		CLog::GetInstance().LogError(LOG_NAME, "Failed to bind socket with error %s", Net::GetLastErrorStr(Net::GetSocketLastError()).c_str());
		return;
	}


	if (listen(m_clientlistnerSocket, SOMAXCONN)== INVALID_SOCKET)
	{
		CLog::GetInstance().LogError(LOG_NAME, "Failed to listen on socket  with error %s", Net::GetLastErrorStr(Net::GetSocketLastError()).c_str());
		return;
	}

	CLog::GetInstance().LogMessage(LOG_NAME, "Game server started.");

	std::thread ping_pong{ &ServerControl::PingPong, this };


	while (!quit_flag)
	{
		sockaddr_in incomingAddr;
		socklen_t incomingAddrSize = sizeof(sockaddr_in);
		SOCKET incomingSocket = accept(m_clientlistnerSocket, reinterpret_cast<sockaddr*>(&incomingAddr), &incomingAddrSize);

		CLog::GetInstance().LogMessage(LOG_NAME, "Accept Client : %s:%d\n", inet_ntoa(incomingAddr.sin_addr), ntohs(incomingAddr.sin_port));
					
		m_pConnectionHandler = new TaskSocket(incomingSocket, incomingAddr);
		m_pConnectionHandler->Start();

		

		Channel.push_back(m_pConnectionHandler);
		
	}

	Net::CloseSocket(m_clientlistnerSocket);
}



void ServerControl::PingPong()
{
	/*std::chrono::minutes mins{ 3 };
	std::chrono::seconds secs{ 15 };*/

	std::chrono::minutes mins{ 1 };
	std::chrono::seconds secs{ 5 };



			//PingMessage pingMsg(1);
			//Framework::CBasePacket basepacket;

			//basepacket.SetTargetId(1);
			//basepacket.SetSourceId(1);
			//basepacket.ToPacketData();
			//basepacket.addSubPacket(pingMsg);

			//SendToAllClient(&basepacket.GetData());
	
	
}



void ServerControl::SendToAllClient(const Framework::PacketData* msg)
{
	int iSendSize = -1;
	if (msg->size()<0) 
		throw SocketException("Bad Message");
	
	for (const auto& client : Channel)
		 client->QueuePacket((Framework::PacketData)*msg);		
	
};


