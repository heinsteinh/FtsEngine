#pragma once


#include <cstdint>
#include <vector>

namespace Framework
{
	enum STREAM_SEEK_DIRECTION
	{
		STREAM_SEEK_SET = 0,
		STREAM_SEEK_END = 1,
		STREAM_SEEK_CUR = 2,
	};

	class CStream
	{
	public:
		virtual	~CStream();
		virtual void	Seek(int64_t, STREAM_SEEK_DIRECTION) = 0;
		
		virtual uint64_t 	Tell() = 0;
		virtual uint64_t 	Read(void*, uint64_t) = 0;
		virtual uint64_t 	Write(const void*, uint64_t) = 0;
		
		virtual bool	IsEOF() = 0;
		virtual void	Flush();
		
		virtual uint64_t	GetLength();
		virtual uint64_t	GetRemainingLength();


		uint8_t		Read8();
		uint16_t	Read16();
		uint32_t	Read32();
		uint64_t	Read64();
		uint16_t	Read16_MSBF();
		uint32_t	Read32_MSBF();
		float		ReadFloat32();
		
		std::string	ReadString();
		std::string	ReadString(size_t);

		void	Write8(uint8_t);
		void	Write16(uint16_t);
		void	Write32(uint32_t);
	};
}