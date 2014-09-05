#pragma once

#include "MemStream.h"
#include "Compack.h"


namespace Framework
{
	struct PACKETHEADER
	{
		uint32_t CheckCode;  
		uint16_t packetSize;
		uint16_t unknown0;  
		uint32_t unknown1[6];
	};

	static_assert(sizeof(PACKETHEADER) == 0x20, "Packet header size must be 32 bytes.");

#define PACKET_HEADER_SIZE sizeof(PACKETHEADER)


	struct SubHeaderProtocol
	{
		uint16_t subSessionId;
		uint16_t subCount_;
		uint16_t subIndex_;
		uint16_t subSize_;
		uint32_t subUnknown0;
		uint32_t subUnknown1;
	};

	struct SUBPACKETHEADER
	{
		uint16_t subPacketSize;
		uint16_t subCommandId;
		uint32_t unknown1;
		uint32_t unknown2;
		uint32_t unknown3;
	};

	static_assert(sizeof(SUBPACKETHEADER) == 0x10, "sub Packet header size must be 16 bytes.");
	static_assert(sizeof(SubHeaderProtocol) == 0x10, "sub Packet header size must be 16 bytes.");
	

#define PACKET_SUBHEADER_SIZE sizeof(SUBPACKETHEADER)

	typedef std::vector<uint8_t> PacketData;
	typedef std::vector<PacketData> SubPacketArray;


	struct SUBPACKET
	{
		SUBPACKETHEADER header;
		PacketData		m_vData;
	};



	class CPacketUtils
	{
	public:
		static bool						HasPacket(Framework::CMemStream&);
		static PacketData			ReadPacket(Framework::CMemStream&);
		static SubPacketArray	SplitPacketSubPacket(const PacketData&);
		static std::string		DumpPacket(const PacketData&);
		static uint16_t				GetSubPacketCommand(const PacketData&);
		static void						EncryptPacket(PacketData&);
		static PacketData			DecryptSubPacket(const PacketData&);
	};
}