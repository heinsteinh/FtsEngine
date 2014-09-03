#include "stdafx.h"
#include "BlockSocket.h"
#include "Log.h"


#include "MutexHelper.h"
#include "CommonSocket.h"
#include <thread>
#include <mutex>
#include <condition_variable>


#define LOG_NAME "BlockSocket"

namespace Framework
{

	struct BlockSocketData
	{
		SOCKET m_inSocket;

		std::thread m_iWriteThread, m_iReadThread;

		std::mutex m_iWriteMutex, m_iReadMutex, m_iStateMutex;
		std::condition_variable m_iWriteCond, m_iReadCond;
	};
}

using namespace Framework;





BlockSocket::BlockSocket()
{

	// Initialize network
	if (!Net::InitNetwork())
	{
		CLog::GetInstance().LogError(LOG_NAME, "Could not init network.\r\n");
	}

	m_psData = new BlockSocketData;
	m_bRunning = false;;

	m_psData->m_inSocket = -1;
	m_eState = STATE_DISCONNECTED;



	m_iNextmessage = 0;
}


BlockSocket::~BlockSocket()
{

	Disconnect(QUEUE_CLEAR);
	ClearWriteQueue();
	ClearReadQueue();

	m_psData->m_inSocket = -1;

	

	delete m_psData;
	m_psData = NULL;

	m_bRunning = false;

	// This is okay, even for multiple sockets. There is an internal counter
	Net::UninitNetwork();
	Net::ShutDownRecv(m_psData->m_inSocket);
	Net::ShutDownRecv(m_psData->m_inSocket);

}


SOCKET BlockSocket::GetSocket()
{
	return m_psData->m_inSocket;
}


void BlockSocket::Shutdown()
{
	Net::ShutDownRecv(m_psData->m_inSocket);
	Net::ShutDownSend(m_psData->m_inSocket);
	Net::CloseSocket(m_psData->m_inSocket);	
}



bool BlockSocket::Connect(std::string p_strAddress, uint16_t p_sPort)
{
	MutexHelper inStateHelper(&m_psData->m_iStateMutex);
	Disconnect(QUEUE_CLEAR);
	ClearReadQueue();
	m_eState = STATE_CONNECTING;
	
	
	// Open new socket
	m_psData->m_inSocket = Net::Connect(p_strAddress, p_sPort, Net::TYPE_TCP);
	if (m_psData->m_inSocket == -1)
	{
		CLog::GetInstance().LogError(LOG_NAME, "Could not open socket.\r\n");
		m_eState = STATE_DISCONNECTED;
		return false;
	}



	m_bRunning = true;

	// Start worker threads
	m_psData->m_iWriteThread = std::thread(std::bind(&BlockSocket::WriteLoop, this));
	m_psData->m_iReadThread = std::thread(std::bind(&BlockSocket::ReadLoop, this));


	m_eState = STATE_CONNECTED;

	// TODO: check protocol version
	return true;
}


void BlockSocket::WritePacket(PacketData& pPacket)
{
	if (&pPacket == NULL)
	{
		return;
	}
	m_inWriteQueue.push(pPacket);
}



void BlockSocket::ReadPacket(bool bWait, PacketData& packet)
{

	if (bWait)
		packet = m_inReadQueue.wait_pop();
	else
		m_inReadQueue.try_pop(packet);
}


void BlockSocket::WriteLoop()
{

	CLog::GetInstance().LogMessage(LOG_NAME, "Starting write loop...\r\n");
	PacketData packet;

	int iSendSize = 0;
	while (m_eState == STATE_CONNECTING)
	{
		std::this_thread::yield();
	}


	while (m_bRunning && (IsConnected() || (m_eState == STATE_DISCONNECTING && m_eWriteBehavior != QUEUE_CLEAR)))
	{
		packet = m_inWriteQueue.wait_pop();
		if (&packet == nullptr)
		{
			// Should never happen, but who knows...
			m_bRunning = false;
			continue;
			
		}
		else
		{
			iSendSize = Net::Send(m_psData->m_inSocket, (char*)packet.data(), packet.size());	
		}

		std::this_thread::yield();
	}
}



void BlockSocket::ReadLoop()
{

	CLog::GetInstance().LogMessage(LOG_NAME, "Starting read loop...\r\n");

	while (m_eState == STATE_CONNECTING)
	{
		std::this_thread::yield();
	}



	while (m_bRunning && IsConnected())
	{		

		if (ReadPacket() == -1)
		{
			m_bRunning = false;
			break;
		}			

		if (CPacketUtils::HasPacket(m_incomingStream))
		{
			auto incomingPacket = CPacketUtils::ReadPacket(m_incomingStream);
			if (incomingPacket.size() <= 0)
			{
				CLog::GetInstance().LogError(LOG_NAME, "Failed to read packet. Disconnecting.\r\n");
				m_bRunning = false;		
				
			}

			m_inReadQueue.push(incomingPacket);
		}

	}
}




int BlockSocket::SendPacket()
{
	//Write to socket
	int totalSent = 0;
	while (!m_inWriteQueue.empty())
	{
		if (totalSent >= 0x1000)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			break;
		}

		PacketData nextPacket;
		nextPacket = m_inWriteQueue.wait_pop();

		int iSendSize = -1;
		if (!SendPacket(nextPacket, iSendSize))
		{
			CLog::GetInstance().LogError(LOG_NAME, "Failed to send packet to client. Disconnecting.\r\n");
			return -1;
		}
	
		totalSent += iSendSize;
	}


	return totalSent;
}



int BlockSocket::ReadPacket()
{
	static const unsigned int maxPacketSize = 0x10000;
	uint8_t incomingPacket[maxPacketSize];
	int read = Net::Recv(m_psData->m_inSocket, reinterpret_cast<char*>(incomingPacket), maxPacketSize);
	if (read == 0)
	{
		//Client disconnected
		CLog::GetInstance().LogError(LOG_NAME, "Client disconnected.");
		return -1;
	}

	if (read > 0)
	{
		m_incomingStream.Write(incomingPacket, read);
	}

	return read;
}


void BlockSocket::ClearWriteQueue()
{
	MutexHelper inStateHelper(&m_psData->m_iStateMutex);

	if (IsConnected() || (m_eState == STATE_DISCONNECTING && m_eWriteBehavior != QUEUE_CLEAR))
	{
		return;
	}

	m_inWriteQueue.empty();
}


void BlockSocket::ClearReadQueue()
{
	MutexHelper inStateHelper(&m_psData->m_iStateMutex);
	if (IsConnected())
	{
		return;
	}

	m_inReadQueue.empty();

}


bool BlockSocket::IsConnected()
{
	return m_eState == STATE_CONNECTED;
}


BlockSocket::State BlockSocket::GetState()
{
	return m_eState;
}


void BlockSocket::Disconnect(QueueBehavior p_eWriteBehavior)
{
	MutexHelper inStateHelper(&m_psData->m_iStateMutex);
	{
		if (m_eState != STATE_DISCONNECTED)
		{
			

			m_eState = STATE_DISCONNECTING;
			m_eWriteBehavior = p_eWriteBehavior;


			// Release waiting clients for reading
			m_psData->m_iReadCond.notify_all();

			if (p_eWriteBehavior != QUEUE_FLUSH_ASYNC)
			{
				// Unlock semaphore so write thread may exit
				m_psData->m_iWriteCond.notify_one();

				if (m_psData->m_iWriteThread.joinable())
					m_psData->m_iWriteThread.join();

				ClearWriteQueue();

				m_psData->m_inSocket;
				m_eState = STATE_DISCONNECTED;
			}

			m_bRunning = false;
		}
	}
}



bool BlockSocket::SendPacket(PacketData& packet, int& iSendSize)
{
	bool success(true);
	

	int size = packet.size();
	int offset = 0;
	std::size_t send_size = 0;

	iSendSize = -1;
	do{
		send_size = ::send(m_psData->m_inSocket, (char *)packet.data() + offset, size, 0);
		if (send_size == -1)
		{
			CLog::GetInstance().LogError(LOG_NAME, "Send error WSAGetLastError = %d\n", WSAGetLastError());			
			success = false;
			iSendSize = -1;
			return success;

		}
		else if (send_size == 0)
		{
			CLog::GetInstance().LogError(LOG_NAME, "Socket Close\n");
			success = false;


			Net::CloseSocket(m_psData->m_inSocket);
			iSendSize = -1;
			return success;
		}

		offset = offset + send_size;

	} while (offset != size);

	iSendSize = offset;

	return success;
}

bool BlockSocket::ReadPacket(PacketData& packet, int& iReadSize)
{
	bool success(true);

	// Receive header
	unsigned int curr = 0;

	size_t bytesreceived = 0;
	PACKETHEADER header;

	// allocate memory for content
	PacketData bufferHeader;
	bufferHeader.reserve(sizeof(PACKETHEADER));


	//Receiver Header
	curr = 0;
	do {
		if ((bytesreceived = Net::Recv(m_psData->m_inSocket, (char*)bufferHeader.data() + curr, (PACKET_HEADER_SIZE)-curr)) == SOCKET_ERROR)
		{
			CLog::GetInstance().LogError(LOG_NAME, "Receive error WSAGetLastError = %d ", WSAGetLastError());
			success = false;
			return success;
		}

		if (bytesreceived == 0) {
			CLog::GetInstance().LogError(LOG_NAME, "Socket Close = %d", WSAGetLastError());
			success = false;
			
			Net::CloseSocket(m_psData->m_inSocket);
			return success;
		}

		curr += bytesreceived;

	} while (curr < PACKET_HEADER_SIZE);



	header = *reinterpret_cast<const PACKETHEADER*>(bufferHeader.data());	
	m_incomingStream.Write(bufferHeader.data(), bufferHeader.size());



	PacketData bufferData;
	bufferData.reserve(header.packetSize - PACKET_HEADER_SIZE);

	//Receiver contents
	curr = 0;
	do {
		if ((bytesreceived = Net::Recv(m_psData->m_inSocket, (char*)bufferData.data() + curr, (header.packetSize - PACKET_HEADER_SIZE) - curr)) == SOCKET_ERROR) {
			CLog::GetInstance().LogError(LOG_NAME, "E_SOCKET_RECEIVE_FAILED %d", WSAGetLastError);
			success = false;
			return success;
		}

		if (bytesreceived == 0) {
			CLog::GetInstance().LogError(LOG_NAME, "E_SOCKET_CLOSED");
			success = false;
			
			Net::CloseSocket(m_psData->m_inSocket);
			return success;
		}

		curr += bytesreceived;

	} while (curr < (header.packetSize - PACKET_HEADER_SIZE));

	m_incomingStream.Write(bufferData.data(), bufferData.size());


	if (CPacketUtils::HasPacket(m_incomingStream))
	{
		auto incomingPacket = CPacketUtils::ReadPacket(m_incomingStream);
		if (incomingPacket.size() == 0)
		{
			CLog::GetInstance().LogError(LOG_NAME, "Failed to read packet. Disconnecting.\r\n");
			m_bRunning = false;
		}

		m_inReadQueue.push(incomingPacket);
	}
	

	return success;
}

