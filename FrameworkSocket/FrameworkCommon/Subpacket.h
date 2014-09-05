#pragma once

#include "Compack.h"
//#include "PacketUtils.h"
//https://github.com/asmloverX/childish-codes/blob/fe4697d2c85283044b7e5202de87e804cac8e4aa/sl_network/sl_network/inc/sl_netprotocol.h
//https://github.com/nueks/reactor/blob/0863ae75a3d325887ace8d387dd104413628abb1/reactor/buffer.hpp

namespace  SL
{
	typedef unsigned char byte;
	typedef unsigned short ushort;
	typedef unsigned long ulong;

	namespace Framework
	{
		struct SubHeaderProtocol;
	}

	class SubPacket
	{
		ushort sessionId_; // session ID of this SubPacket
		ushort count_;	 	 // count of SubPacket in one Packet
		ushort index_;		 // index of SubPacket in one Packet
		ushort size_;			 // size of this SubPacket
		byte* data_;			 // data of this SubPacket

	public:
		SubPacket(void);
		SubPacket(const struct Framework::SubHeaderProtocol* np, const byte* data);
		SubPacket(ushort sessionId, ushort count, ushort index, ushort size, const byte* data);
		virtual ~SubPacket(void);

	public:
		bool setValue(const struct Framework::SubHeaderProtocol* np, const byte* data);
		bool setValue(ushort sessionId, ushort count,	ushort index, ushort size, const byte* data);


		const ushort GetSessionId(void) const;
		const ushort GetCount(void) const;
		const ushort GetIndex(void) const;
		const ushort GetSize(void) const;
		const byte* GetData(void) const;

	};

	// Class Packet
	//
	// example:
	// sl::Packet p;
	// 1> create a Packet instance
	// p.create(SubPacketCountsOfThisPacket);
	// 2> add SubPacket to Packet or get data from Packet
	// SubPacket sp(NetProtocolHead, SubPacketData);
	// p.add(sp);
	// ...
	// byte buf[100] = {0};
	// p.getData(sizeof(buf), (byte*)buf);
	// or
	// memcpy(buf, p.getData(), sizeof(buf));
	// 3> release this Packet instance after use
	// p.release();

	class Packet
	{
		ushort sessionId_; // session ID of this Packet
		ulong size_;			 // size of this full Packet
		byte* data_;			 // data of this full Packet

	public:
		Packet(void);
		~Packet(void);

	public:
		bool create(ushort subPackCount = 1);
		void release(void);
		const ushort getSessionId(void) const;
		const ulong getSize(void) const;
		bool addSubPacket(const SubPacket& sp);
		bool getData(ulong size, byte* data);
		const byte* getData(void) const;
	};



}


