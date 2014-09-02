#include "stdafx.h"



#include "BasePacket.h"
#include <assert.h>


using namespace Framework;


CBasePacket::CBasePacket() : m_packetSize(sizeof(PACKETHEADER)), m_sourceId(0), m_targetId(0), m_commandId(0)
{
	m_vData.resize(sizeof(PACKETHEADER));
}

CBasePacket::~CBasePacket()
{
}

PacketPtr CBasePacket::Clone() const
{
	return std::make_shared<CBasePacket>(*this);
}

void CBasePacket::SetSourceId(uint32_t sourceId)
{
	m_sourceId = sourceId;
}

void CBasePacket::SetTargetId(uint32_t targetId)
{
	m_targetId = targetId;
}


PacketData CBasePacket::ToPacketData() 
{
	
	
	assert(m_packetSize >= sizeof(PACKETHEADER));
	assert(m_sourceId != 0);
	assert(m_targetId != 0);

	int iSize = sizeof(PACKETHEADER);

	PACKETHEADER header;
	header.packetSize = iSize;
	header.CheckCode = 0x1D;
	header.unknown0 = 0xFF;
	header.unknown1[0] = 0xFFFF;
	header.unknown1[1] = 0xFFFF;
	header.unknown1[2] = 0xFFFF;
	header.unknown1[3] = 0xFFFF;
	header.unknown1[4] = 0xFFFF;
	header.unknown1[5] = 0xFFFF;

	memcpy(m_vData.data(), &header, sizeof(PACKETHEADER));
	
	return m_vData;
}

PacketData CBasePacket::addSubPacket(SUBPACKET& subPacket)
{

	PacketData tmpData;
	int OldPackSize;

	PACKETHEADER header = *reinterpret_cast<PACKETHEADER*>(m_vData.data());
	uint8_t* data = reinterpret_cast<uint8_t*>(m_vData.data() + sizeof(PACKETHEADER));

	OldPackSize = header.packetSize;
	header.packetSize = OldPackSize + subPacket.header.subPacketSize;
	
	tmpData.resize(header.packetSize);
	memcpy(tmpData.data(), &header, sizeof(PACKETHEADER));

	int RemainingData = OldPackSize - sizeof(PACKETHEADER);
	memcpy(tmpData.data() + sizeof(PACKETHEADER), data, RemainingData);

	memcpy(tmpData.data() + OldPackSize, subPacket.m_vData.data(), subPacket.header.subPacketSize);


	m_vData.clear();
	m_vData.resize(header.packetSize);
	memcpy(m_vData.data(), tmpData.data(), header.packetSize);

	return m_vData;
	
}


PACKETHEADER CBasePacket::Getheader()
{
	return *reinterpret_cast<PACKETHEADER*>(m_vData.data());	
}