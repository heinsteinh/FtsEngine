#include "stdafx.h"
#include "ConnectionHandler.h"

#include "../FrameworkCommon/Log.h"


#include <chrono>
using namespace Framework;

#define LOG_NAME "ConnectionHandler"


ConnectionHandler::ConnectionHandler(SOCKET clientSocket, sockaddr_in clientAddress) : m_pClientSocket(clientSocket), m_clientAddress(clientAddress)
{
	m_bDisconnect = false;
	m_bIsPinged = false;
	
}



ConnectionHandler::~ConnectionHandler(void)
{
	closesocket(m_pClientSocket);


	if (m_ConnectionThread->joinable())
		m_ConnectionThread->join();

	
	m_bIsPinged = false;

	CLog::GetInstance().LogMessage(LOG_NAME, "Disconnecting Client : %s:%d\n", inet_ntoa(m_clientAddress.sin_addr), ntohs(m_clientAddress.sin_port));
}


void ConnectionHandler::Start()
{

	u_long notBlockingMode = 0;
	ioctlsocket(m_pClientSocket, FIONBIO, &notBlockingMode);

	m_bDisconnect = false;
	m_ConnectionThread = std::shared_ptr<std::thread>(new std::thread(std::bind(&ConnectionHandler::Run, this)));
	m_ConnectionThread->detach();
}



bool ConnectionHandler::IsConnected() { return m_bDisconnect; }


void ConnectionHandler::Run()
{

	char *addr;
	addr = inet_ntoa(m_clientAddress.sin_addr);
	CLog::GetInstance().LogMessage(LOG_NAME, "Receiving Connection from %s. ", addr);

	m_bDisconnect = false;



	while (!m_bDisconnect)
	{
		//Write to socket
		{
			int totalSent = 0;
			while (!m_packetQueue.empty())
			{
				if (totalSent >= 0x1000)
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(100));
					break;
				}
				const auto& nextPacket = m_packetQueue.front();
				int sent = send(m_pClientSocket, reinterpret_cast<const char*>(nextPacket.data()), nextPacket.size(), 0);
				if (sent != nextPacket.size())
				{
					CLog::GetInstance().LogError(LOG_NAME, "Failed to send packet to client. Disconnecting.\r\n");
					m_bDisconnect = true;
					return;
				}
				m_packetQueue.pop_front();
				totalSent += sent;
			}
		}


		//Read from socket
		{
		static const unsigned int maxPacketSize = 0x10000;
		uint8_t incomingPacket[maxPacketSize];
		int read = recv(m_pClientSocket, reinterpret_cast<char*>(incomingPacket), maxPacketSize, 0);
		if (read == 0)
		{
			CLog::GetInstance().LogMessage(LOG_NAME, "Client disconnected.");
			m_bDisconnect = true;
			return;
		}
		if (read > 0)
		{
			m_incomingStream.Write(incomingPacket, read);
		}


		HandleClientMessage(m_incomingStream);
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}

	}

	delete(this);

}



void ConnectionHandler::QueuePacket(const PacketData& packet)
{
	m_packetQueue.push_back(packet);
}



void ConnectionHandler::HandleClientMessage(Framework::CMemStream& incomingStream)
{

	if (CPacketUtils::HasPacket(incomingStream))
	{
		auto incomingPacket = CPacketUtils::ReadPacket(incomingStream);
		if (incomingPacket.size() == 0)
		{
			CLog::GetInstance().LogError(LOG_NAME, "Failed to read packet. Disconnecting.\r\n");
			return;
		}

		printf("%s", CPacketUtils::DumpPacket(incomingPacket).c_str());

		unsigned int clientId = incomingPacket[0x02];
		auto subPackets = CPacketUtils::SplitPacketSubPacket(incomingPacket);
		for (const auto& subPacket : subPackets)
		{
			uint16_t commandId = CPacketUtils::GetSubPacketCommand(subPacket);
			/*switch (commandId)
			{

			case ClientToServerPackageHdr::CONNECT:
				ProcessConnectOk(subPacket);
				break;

			case ServerToClientPackageHdr::TOUR_INFO:
				ProcessChat(subPacket);
				break;

			case ServerToClientPackageHdr::SELECT_OK:
				ProcessChat(subPacket);
				break;

			case ServerToClientPackageHdr::PLAYERS_INFO:
				ProcessChat(subPacket);
				break;

			case ClientToServerPackageHdr::KEEP_ALIVE:
				ProcessKeepAlive(subPacket);
				break;

			}*/
		}
	}
}
