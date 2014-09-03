#pragma once

#include <vector>
#include <thread>
#include <memory>
#include <deque>


#include "../FrameworkCommon/MemStream.h"
#include "../FrameworkCommon/Compack.h"
#include "../FrameworkCommon/PacketUtils.h"

#include "Message.h"


class ConnectionHandler
{


	typedef std::deque<Framework::PacketData> PacketQueue;


	
	SOCKET													m_pClientSocket;
	std::shared_ptr<std::thread>		m_ConnectionThread;
	Framework::CMemStream						m_incomingStream;
	bool														m_bDisconnect;
	sockaddr_in											m_clientAddress;

	PacketQueue											m_packetQueue;

	void														Run();
	
	bool														m_bIsPinged;
	bool														m_bQuitFlag;


public:
	ConnectionHandler(SOCKET pClient, sockaddr_in _clientAddress);
	~ConnectionHandler();


	void	QueuePacket(const Framework::Message&);
	

	void HandleClientMessage(Framework::CMemStream&);
	int RecvPacket(Framework::Message& packet);


	void	PrepareInitialPackets();

	//void	ProcessInitialHandshake(unsigned int, const Framework::PacketData&);
	//void	ProcessKeepAlive(const Framework::PacketData&);
	//void	ProcessChat(const Framework::PacketData&);

	void ProcessConnectOk(const Framework::Message&);


	void Start();
	bool IsConnected();

	void QueuePacket(const Framework::PacketData& packet);

	
	
	bool IsPinged()			{ return m_bIsPinged; };
	void SetPinged()		{ m_bIsPinged = true; };
	void SetUnPinged()	{ m_bIsPinged = false; };
	
	
};

