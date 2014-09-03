#pragma once

#include <atomic>
#include <queue>
#include "ConcurrentQueue.h"
#include "PacketUtils.h"

namespace Framework
{

	struct BlockSocketData;
	class BlockSocket
	{

	public:
		enum State
		{
			STATE_DISCONNECTED,
			STATE_CONNECTING,
			STATE_CONNECTED,
			STATE_DISCONNECTING
		};

		enum QueueBehavior
		{
			QUEUE_CLEAR,
			QUEUE_FLUSH_WAIT,
			QUEUE_FLUSH_ASYNC
		};



	private:
		typedef ConcurrentQueue<PacketData> PacketList;

		PacketList m_inWriteQueue, m_inReadQueue;
		QueueBehavior m_eWriteBehavior;
		State m_eState;


		CMemStream					m_incomingStream;
		BlockSocketData*		m_psData;
		std::atomic<bool>		m_bRunning;
		int									m_iNextmessage;


		


	public:
		BlockSocket();
		~BlockSocket();


		void WriteLoop();
		void ReadLoop();


		bool Connect(std::string p_strAddress, uint16_t p_sPort);
		void Disconnect(QueueBehavior p_eWriteBehavior);


		void WritePacket(PacketData& pPacket);
		void ReadPacket(bool bWait, PacketData& packet);


		size_t GetWriteQueueSize();
		size_t GetReadQueueSize();

		void ClearReadQueue();
		void ClearWriteQueue();
		
		bool IsConnected();
		State GetState();


		int SendPacket();
		int ReadPacket();


		bool SendPacket(PacketData& packet, int& iSendSize);
		bool ReadPacket(PacketData& packet, int& iReadSize);



		SOCKET GetSocket();
		void Shutdown();

	/*	int SendTCPPacket(int sock, char *buf, int size);
		int RecvTCPPacket(int sock, PacketData& packet);
		int RecvTCPPacket(int sock, char *buf, int size);*/
	};


}