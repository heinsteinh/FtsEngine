#pragma once



#include <memory>
#include "PacketUtils.h"
//https://github.com/ioquatix/dream/blob/db1b97f830d231e6a59840b68c3bc35563c21693/source/Dream/Network/Message.h

/// The message header contains the type and length of the message that has been sent or received.
//struct alignas(32) MessageHeader{
//	/// The length in bytes.
//	Core::Ordered<uint32_t> length;
//	/// The packet type.
//	Core::Ordered<uint16_t> packet_type;
//};

/** A message that can be sent across the network.
This class aids in the construction and interpretation of structured data sent across the network. It provides a basic header structure and size
information so discrete data can be conveniently sent across the network. It ties in with MessageClientSocket which can send and receive messages
reliably.

*/

namespace Framework
{
	class CBasePacket;
	typedef std::shared_ptr<CBasePacket> PacketPtr;
	class CBasePacket
	{
	public:

		

		CBasePacket();
		virtual	~CBasePacket();
		virtual PacketPtr	Clone() const;
		void	SetSourceId(uint32_t);
		void	SetTargetId(uint32_t);
		virtual PacketData	ToPacketData() ;
		PacketData addSubPacket(SUBPACKET& subPacket);
		
		PacketData GetData() { return m_vData; }
		PACKETHEADER Getheader();

	protected:
		uint16_t	m_packetSize;
		uint32_t	m_sourceId;
		uint32_t	m_targetId;
		uint16_t	m_commandId;
		PacketData  m_vData;
	};		 
}