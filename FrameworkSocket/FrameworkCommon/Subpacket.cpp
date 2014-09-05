#include "stdafx.h"
#include "Subpacket.h"

#include "Compack.h"
#include "PacketUtils.h"

#include <sstream>

//https://github.com/asmloverX/childish-codes/blob/fe4697d2c85283044b7e5202de87e804cac8e4aa/sl_network/sl_network/src/sl_packet.cc

#define SL_NETPROTO_PORT_DEF (20093) // default network port
#define SL_NETPROTO_SIGNATURE (0xA9EE) // network protocol signature
#define SL_NETPROTO_VERSION (0x0100) // network protocol version
#define SL_NETPROTO_PACKET_SZ (768) // size of network protocol packet


namespace SL
{

	SubPacket::SubPacket(void)
	{
		memset(this, 0, sizeof(*this));
	}

	SubPacket::SubPacket(const struct Framework::SubHeaderProtocol* np, const byte* data)
	{
		memset(this, 0, sizeof(*this));
		setValue(np, data);
	}

	SubPacket::SubPacket(ushort sessionId, ushort count,	ushort index, ushort size, const byte* data)
	{
		memset(this, 0, sizeof(*this));
		setValue(sessionId, count, index, size, data);
	}

	SubPacket::~SubPacket(void)
	{
	}

	bool SubPacket::setValue(const Framework::SubHeaderProtocol* np, const byte* data)
	{
		if (NULL != np && NULL != data)
		{

			/*
			sessionId_ = np->subSessionId;			
			count_ = np->subCount_;
			index_ = np->subIndex_;
			size_ = np->subSize_;*/

			data_ = (byte*)data;
			return true;
		}
		return false;
	}

	bool SubPacket::setValue(ushort sessionId, ushort count,	ushort index, ushort size, const byte* data)
	{
		if (NULL != data)
		{
			sessionId_ = sessionId;
			count_ = count;
			index_ = index;
			size_ = size;
			data_ = (byte*)data;
			return true;
		}
		return false;
	}

	const ushort SubPacket::GetSessionId(void) const
	{
		return sessionId_;
	}
	const ushort SubPacket::GetCount(void) const
	{
		return count_;
	}
	const ushort SubPacket::GetIndex(void) const
	{
		return index_;
	}
	const ushort SubPacket::GetSize(void) const
	{
		return size_;
	}
	const byte* SubPacket::GetData(void) const
	{
		return (const byte*)data_;
	}





	Packet::Packet(void)
	{
		memset(this, 0, sizeof(*this));
	}

	Packet::~Packet(void)
	{
	}
	
	bool Packet::create(ushort subPackCount)
	{
		if (subPackCount > 0)
		{
			if (NULL != data_)
				return true;
			data_ = (byte*)calloc(subPackCount, SL_NETPROTO_PACKET_SZ);
			return (NULL != data_);
		}
		return false;
	}
	void Packet::release(void)
	{
		if (NULL != data_)
		{
			free(data_);
			data_ = NULL;
		}
		size_ = 0L;
		sessionId_ = 0;
	}
	const ushort Packet::getSessionId(void) const
	{
		return sessionId_;
	}
	const ulong Packet::getSize(void) const
	{
		return size_;
	}
	bool Packet::addSubPacket(const SubPacket& sp)
	{
		if (NULL != data_ && sp.GetSize() > 0)
		{
			sessionId_ = sp.GetSessionId();
			memcpy(data_ + (sp.GetIndex() - 1) * SL_NETPROTO_PACKET_SZ,	sp.GetData(), sp.GetSize());
			size_ += sp.GetSize();
			return true;
		}
		return false;
	}
	bool Packet::getData(ulong size, byte* data)
	{
		if (NULL != data_ && NULL != data)
		{
			memcpy(data, data_, (size >= size_ ? size_ : size));
			return true;
		}
		return false;
	}
	const byte* Packet::getData(void) const
	{
		return data_;
	}
}



//
//std::string Subpacket::write_subpacket(const std::string & data) const
//{
//		return std::string(1, data.size()) + data;
//}
//
//
//template <typename T>
//void Subpacket::writeVal(T& val)
//{
//	val = (T)(*(T*)(data. + offset_));
//	offset_ += sizeof(T);
//}
//
//
//std::string Subpacket::show_title() const{
//	std::stringstream out;
//	out << " " << Subpacket_Tags.at(type) << " Subpacket (sub " << static_cast <unsigned int> (type) << ") (" << size << " octets)";
//	return out.str();
//}
//
//Subpacket::Subpacket(uint8_t type, unsigned int size) :
//type(type),
//size(size)
//{}
//
//Subpacket::~Subpacket(){}
//
//std::string Subpacket::write() const{
//	return write_subpacket(std::string(1, type) + raw());
//}
//
//uint8_t Subpacket::get_type() const{
//	return type;
//}
//
//unsigned int Subpacket::get_size() const{
//	return size;
//}
//
//void Subpacket::set_type(uint8_t t){
//	type = t;
//}
//
//void Subpacket::set_size(unsigned int s){
//	size = s;
//}
//
//Subpacket::Subpacket(const Subpacket & copy) :
//type(copy.type),
//size(copy.size)
//{}
//
//Subpacket & Subpacket::operator =(const Subpacket & copy){
//	type = copy.type;
//	size = copy.size;
//	return *this;
//}