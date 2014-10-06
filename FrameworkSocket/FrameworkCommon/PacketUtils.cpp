
#include "PacketUtils.h"
#include "Log.h"
#include "Blowfish.h"

#define LOG_NAME "PacketUtils"



namespace Framework
{

	bool CPacketUtils::HasPacket(Framework::CMemStream& stream)
	{
		if (stream.GetSize() < sizeof(PACKETHEADER))
		{
			return false;
		}

		stream.Seek(0, Framework::STREAM_SEEK_SET);

		PACKETHEADER header;
		stream.Read(&header, sizeof(PACKETHEADER));
		stream.Seek(0, Framework::STREAM_SEEK_END);

		if (stream.GetSize() < header.packetSize)
		{
			return false;
		}
		return true;
	}


	std::vector<uint8_t> CPacketUtils::ReadPacket(Framework::CMemStream& stream)
	{
		std::vector<uint8_t> result;
		if (!CPacketUtils::HasPacket(stream))
		{
			assert(0);
			return result;
		}
		stream.Seek(0, Framework::STREAM_SEEK_SET);
		PACKETHEADER header;
		stream.Read(&header, sizeof(PACKETHEADER));
		if (header.packetSize < sizeof(PACKETHEADER))
		{
			//Invalid packet
			CLog::GetInstance().LogError(LOG_NAME, "Packet size in header is invalid.\r\n");
			return result;
		}
		stream.Seek(0, Framework::STREAM_SEEK_SET);
		result.resize(header.packetSize);
		stream.Read(&result[0], header.packetSize);
		stream.Truncate();
		stream.Seek(0, Framework::STREAM_SEEK_END);
		return result;
	}



	SubPacketArray CPacketUtils::SplitPacketSubPacket(const PacketData& packet)
	{
		printf("%s", CPacketUtils::DumpPacket(packet).c_str());

		SubPacketArray subPackets;
		if (packet.size() < sizeof(PACKETHEADER))
		{
			CLog::GetInstance().LogError(LOG_NAME, "Packet to split is smaller than PACKETHEADER.\r\n");
			return subPackets;
		}
		const uint8_t* packetData = packet.data();
		PACKETHEADER header = *reinterpret_cast<const PACKETHEADER*>(packetData);
		assert(packet.size() == header.packetSize);
		uint32_t currentSize = header.packetSize - sizeof(PACKETHEADER);
		packetData += sizeof(PACKETHEADER);

		while (currentSize != 0)
		{
			SUBPACKETHEADER subHeader = *reinterpret_cast<const SUBPACKETHEADER*>(packetData);
			if (subHeader.subPacketSize == 0)
			{
				CLog::GetInstance().LogError(LOG_NAME, "Got zero sized subpacket. Stopping packet processing.\r\n");
				break;
			}

			if (subHeader.subPacketSize > currentSize)
			{
				CLog::GetInstance().LogError(LOG_NAME, "Subpacket doesn't fit in packet. Stopping packet processing.\r\n");
				break;
			}

			auto subPacket = PacketData(packetData, packetData + subHeader.subPacketSize);
			subPackets.push_back(subPacket);

			currentSize -= subHeader.subPacketSize;
			packetData += subHeader.subPacketSize;
		}
		return subPackets;
	}


	std::string CPacketUtils::DumpPacket(const PacketData& packet)
	{
		std::string result;
		static const unsigned int lineWidth = 0x10;
		for (unsigned int i = 0; i < (packet.size() + lineWidth - 1) / lineWidth; i++)
		{
			for (unsigned int j = 0; j < lineWidth; j++)
			{
				unsigned int offset = i * lineWidth + j;
				if (offset >= packet.size())
				{
					result += " ";
				}
				else
				{
					char byteString[4];
					sprintf(byteString, "%0.2X ", packet[offset]);
					result += byteString;
				}
			}
			result += " ";
			for (unsigned int j = 0; j < lineWidth; j++)
			{
				unsigned int offset = i * lineWidth + j;
				if (offset >= packet.size()) continue;
				char character = packet[offset];
				if ((character >= 0) && (isdigit(character) || isalpha(character)))
				{
					result += character;
				}
				else
				{
					result += ".";
				}
			}
			result += "\r\n";
		}
		return result;
	}

	uint16_t CPacketUtils::GetSubPacketCommand(const PacketData& subPacket)
	{
		SUBPACKETHEADER header = *reinterpret_cast<const SUBPACKETHEADER*>(subPacket.data());
		return  header.subCommandId;
	}

	void CPacketUtils::EncryptPacket(PacketData& packet)
	{
		if (packet.size() <= sizeof(PACKETHEADER))
		{
			assert(0);
			return;
		}
		uint8_t* data = &packet[0];
		uint32_t size = (uint32_t)packet.size();

		data += sizeof(PACKETHEADER);
		size -= sizeof(PACKETHEADER);


		if (size % 8 != 0)
		{
			return;
		}

		while (1)
		{
			SUBPACKETHEADER subPacket = *reinterpret_cast<SUBPACKETHEADER*>(data);
			uint32_t subPacketSize = subPacket.subPacketSize;

			size -= subPacketSize;
			subPacketSize -= sizeof(SUBPACKETHEADER);
			data += sizeof(SUBPACKETHEADER);

			for (unsigned int i = 0; i < subPacketSize; i += 8)
			{
				Blowfish_encipher(
					reinterpret_cast<uint32_t*>(data + i),
					reinterpret_cast<uint32_t*>(data + i + 4));
			}
			data += subPacketSize;

			if (size == 0)
				break;
		}
	}

	PacketData CPacketUtils::DecryptSubPacket(const PacketData& packet)
	{
		PacketData result(packet);
		SUBPACKETHEADER subHeader = *reinterpret_cast<const SUBPACKETHEADER*>(result.data());

		if (subHeader.subCommandId != 0x03)
			return result;

		uint8_t* subPacketData = result.data() + 8;
		uint32_t decryptSize = (uint32_t)(result.size() - 8);
		for (uint32_t i = 0; i < decryptSize; i += 8)
		{
			Blowfish_decipher(
				reinterpret_cast<uint32_t*>(subPacketData + i),
				reinterpret_cast<uint32_t*>(subPacketData + i + 4));
		}
		return result;
	}


}