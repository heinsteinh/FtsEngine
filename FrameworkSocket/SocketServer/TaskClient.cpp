#include "stdafx.h"
#include "TaskClient.h"

#include "../FrameworkCommon/Log.h"
#include "../FrameworkCommon/BasePacket.h"



#include <chrono>
using namespace Framework;

#define LOG_NAME "TaskSocket"



class KeepAliveRunner: public Framework::Runnable
{
	friend class ConnectionHandler;

public:
	KeepAliveRunner(TaskSocket* con) :_con(con){}
	~KeepAliveRunner(){}

	void Run() override;
private:
	TaskSocket* _con;
};

void KeepAliveRunner::Run()
{

#define KEEP_ALIVE_TIME_INTERVAL 10

	Framework::CBasePacket basepacket;

	basepacket.SetTargetId(1);
	basepacket.SetSourceId(1);
	basepacket.ToPacketData();
	
	std::chrono::seconds dura(KEEP_ALIVE_TIME_INTERVAL);
	std::this_thread::sleep_for(dura);
	_con->QueuePacket(basepacket.GetData());
}



TaskSocket::TaskSocket(SOCKET clientSocket, sockaddr_in clientAddress) : m_pClientSocket(clientSocket), m_clientAddress(clientAddress)
{
	m_bDisconnect = false;
	m_bIsPinged = false;		
	
	m_KeepAliveThread = new Framework::Thread(new KeepAliveRunner(this));

}



TaskSocket::~TaskSocket(void)
{
	closesocket(m_pClientSocket);


	if (m_ConnectionThread && m_ConnectionThread->joinable())
		m_ConnectionThread->join();


	if (m_KeepAliveThread)
	{
		delete m_KeepAliveThread;
		m_KeepAliveThread = NULL;
	}

	
	m_bIsPinged = false;
	CLog::GetInstance().LogMessage(LOG_NAME, "Disconnecting Client : %s:%d\n", inet_ntoa(m_clientAddress.sin_addr), ntohs(m_clientAddress.sin_port));
}


void TaskSocket::Start()
{

	u_long notBlockingMode = 0;
	ioctlsocket(m_pClientSocket, FIONBIO, &notBlockingMode);

	m_bDisconnect = false;
	m_ConnectionThread = std::shared_ptr<std::thread>(new std::thread(std::bind(&TaskSocket::Run, this)));
	m_ConnectionThread->detach();
}



bool TaskSocket::IsConnected() { return m_bDisconnect; }


void TaskSocket::Run()
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

		if (read < 0)
		{
			CLog::GetInstance().LogMessage(LOG_NAME, "Client disconnected.");
			m_bDisconnect = true;

		}

		HandleClientMessage(m_incomingStream);
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}

	}
	
	delete(this);
}



void TaskSocket::QueuePacket(const PacketData& packet)
{
	m_packetQueue.push_back(packet);
}



void TaskSocket::HandleClientMessage(Framework::CMemStream& incomingStream)
{

	if (CPacketUtils::HasPacket(incomingStream))
	{
		auto incomingPacket = CPacketUtils::ReadPacket(incomingStream);
		if (incomingPacket.size() == 0)
		{
			CLog::GetInstance().LogError(LOG_NAME, "Failed to read packet. Disconnecting.\r\n");
			return;
		}

		//printf("%s", CPacketUtils::DumpPacket(incomingPacket).c_str());

		unsigned int clientId = incomingPacket[0x02];
		auto subPackets = CPacketUtils::SplitPacketSubPacket(incomingPacket);
		for (const auto& subPacket : subPackets)
		{
			uint16_t commandId = CPacketUtils::GetSubPacketCommand(subPacket);
			switch (commandId)
			{

			case 32:
				ProcessChat(subPacket);
				break;


				/*
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
				*/
			}
		}
	}
}



void TaskSocket::ProcessConnectOk(const Framework::PacketData&)
{

}

void TaskSocket::ProcessChat(const Framework::PacketData& subPacket)
{

	const Framework::SUBPACKETHEADER header = *reinterpret_cast<const Framework::SUBPACKETHEADER*>(subPacket.data());
	

	CLog::GetInstance().LogMessage(LOG_NAME, "%d :%d :%d :%d \r\n", header.subCommandId, header.subPacketSize, header.unknown1, header.unknown2);


	const char* chatText = reinterpret_cast<const char*>(subPacket.data() + sizeof(Framework::SUBPACKETHEADER));

	//CLog::GetInstance().LogMessage(LOG_NAME, "%s", chatText);
	
}