#pragma once

#include <vector>
#include <thread>
#include <memory>
#include <deque>


#include "../FrameworkCommon/CommonMessage.h"
#include "../FrameworkCommon/MemStream.h"
#include "../FrameworkCommon/Compack.h"
#include "../FrameworkCommon/PacketUtils.h"
#include "../FrameworkCommon/ThreadBase.h"
#include "../FrameworkCommon/TaskQueue.h"

#include "Message.h"


class TaskSocket : public Framework::Task
{
	typedef std::deque<Framework::PacketData> PacketQueue;

		
	SOCKET													m_pClientSocket;
	std::shared_ptr<std::thread>		m_ConnectionThread;
	Framework::CMemStream						m_incomingStream;
	bool														m_bDisconnect;
	sockaddr_in											m_clientAddress;

	PacketQueue											m_packetQueue;


	
	bool														m_bIsPinged;
	bool														m_bQuitFlag;

	Framework::Thread*							m_KeepAliveThread;

public:
	TaskSocket(SOCKET pClient, sockaddr_in _clientAddress);
	~TaskSocket();
		

	void HandleClientMessage(Framework::CMemStream&);
	int RecvPacket(Framework::Message& packet);


	void PrepareInitialPackets();
	void ProcessConnectOk(const Framework::Message&);


	void Start();
	void Run() override;
	bool IsConnected();

	void QueuePacket(const Framework::PacketData& packet);
	void QueuePacket(const Framework::Message&);

	


	
};

