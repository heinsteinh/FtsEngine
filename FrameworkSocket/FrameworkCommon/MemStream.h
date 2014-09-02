#pragma once

#include "Stream.h"
namespace Framework
{
	class CMemStream : public CStream
	{
	public:
		CMemStream();
		CMemStream(const CMemStream&);
		virtual	~CMemStream();
		CMemStream&	operator =(const CMemStream&) = delete;
		uint64_t	Read(void*, uint64_t);
		uint64_t	Write(const void*, uint64_t);
		uint64_t	Tell();

		void	Seek(int64_t, STREAM_SEEK_DIRECTION);
		bool	IsEOF();
		void	ResetBuffer();
		void	Allocate(unsigned int);
		void	Truncate();

		uint8_t*	GetBuffer() const;
		unsigned int	GetSize() const;

	private:
		void	CopyFrom(const CMemStream&);
		unsigned int	m_size = 0;
		unsigned int	m_grow = 0;
		unsigned int	m_position = 0;
		uint8_t*	m_data = nullptr;
		bool	m_isEof = false;
	};
}