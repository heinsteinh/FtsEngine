



#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <stdexcept>
#include <cassert>

#include "MemStream.h"



#define GROWSIZE (0x1000)
using namespace Framework;
CMemStream::CMemStream()
{
}
CMemStream::CMemStream(const CMemStream& src)
{
	CopyFrom(src);
}
CMemStream::~CMemStream()
{
	if (m_data != NULL)
		free(m_data);

	m_data = NULL;

}
void CMemStream::CopyFrom(const CMemStream& src)
{
	assert(m_data == nullptr);
	m_size = src.m_size;
	m_grow = src.m_grow;
	m_position = src.m_position;
	assert(m_grow >= m_size);
	assert(m_position <= m_size);
	m_data = reinterpret_cast<uint8_t*>(malloc(m_grow));
	memcpy(m_data, src.m_data, m_size);
	m_isEof = src.m_isEof;
}
bool CMemStream::IsEOF()
{
	return (m_isEof);
}

uint64_t CMemStream::Tell()
{
	return m_position;
}

void CMemStream::Seek(int64_t position, STREAM_SEEK_DIRECTION dir)
{
	switch (dir)
	{
	case STREAM_SEEK_SET:
		if (position > m_size) throw std::runtime_error("Invalid position.");
		m_position = static_cast<unsigned int>(position);
		m_isEof = false;
		break;
	case STREAM_SEEK_CUR:
		m_position += static_cast<int>(position);
		m_isEof = false;
		break;
	case STREAM_SEEK_END:
		m_position = m_size;
		m_isEof = true;
		break;
	}
}
uint64_t CMemStream::Read(void* data, uint64_t size)
{
	if (m_position >= m_size)
	{
		m_isEof = true;
		return 0;
	}
	unsigned int readSize = std::min(static_cast<unsigned int>(size), m_size - m_position);
	memcpy(data, m_data + m_position, readSize);
	m_position += readSize;
	return readSize;
}
uint64_t CMemStream::Write(const void* data, uint64_t size)
{
	if ((m_position + size) > m_grow)
	{
		assert(m_grow >= m_size);
		m_grow += ((static_cast<unsigned int>(size)+GROWSIZE - 1) / GROWSIZE) * GROWSIZE;
		m_data = reinterpret_cast<uint8_t*>(realloc(m_data, m_grow));
	}
	memcpy(m_data + m_position, data, static_cast<uint32_t>(size));
	m_position += static_cast<unsigned int>(size);
	m_size = std::max<unsigned int>(m_size, m_position);
	return size;
}
void CMemStream::Allocate(unsigned int size)
{
	assert(size >= m_size);
	m_data = reinterpret_cast<uint8_t*>(realloc(m_data, size));
	m_grow = size;
	m_size = size;
}
void CMemStream::ResetBuffer()
{
	m_size = 0;
	m_position = 0;
	m_isEof = false;
}
void CMemStream::Truncate()
{
	m_size = static_cast<uint32_t>(GetRemainingLength());
	assert(m_size <= m_grow);
	memmove(m_data, m_data + m_position, m_size);
	m_position = 0;
}
uint8_t* CMemStream::GetBuffer() const
{
	return m_data;
}
unsigned int CMemStream::GetSize() const
{
	return m_size;
}