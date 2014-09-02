#pragma once


#include <memory>
#include <string>

#include "MemAlloc.h"

namespace Framework
{
	class Buffer
	{
	public:
		Buffer() : ptr_(NULL), size_(0), capacity_(0)
		{
		}

		Buffer(const char* buffer, size_t length) : capacity_(length), size_(length)
		{
			//ptr_ = (char*)::malloc(capacity_);
			ptr_ = (char*)MemAllocT.Alloc(capacity_);
			std::copy(buffer, buffer + length, ptr_);
		}

		Buffer(const char* buffer, size_t length, size_t init_capacity)
			: capacity_(init_capacity),
			size_(length)
		{
			//ptr_ = (char*)::malloc(capacity_);
			ptr_ = (char*)MemAllocT.Alloc(capacity_);
			std::copy(buffer, buffer + length, ptr_);
		}
		explicit Buffer(size_t init_capacity) : ptr_(NULL), size_(0), capacity_(init_capacity)
		{
			if (capacity_ != 0)
				ptr_ = (char*)::malloc(capacity_);
		}

		~Buffer()
		{
			if (ptr_)
				MemAllocT.Dealloc(ptr_, capacity_);
				//::free(ptr_);
		}

		void capacity(size_t new_capacity)
		{
			if (new_capacity <= capacity_)
				return;
			capacity_ = new_capacity;
			char* old_ptr = ptr_;
			ptr_ = (char*)malloc(capacity_);
			if (old_ptr)
			{
				::memmove(ptr_, old_ptr, size_);
			}
			free(old_ptr);
		}
		void resize(size_t new_size)
		{
			if (new_size <= capacity_)
			{
				size_ = new_size;
				return;
			}
			capacity(new_size);
			size_ = new_size;
		}
		size_t size() const { return size_; }
		size_t capacity() const { return capacity_; }
		size_t remain() const { return capacity_ - size_; }
		operator char*() { return ptr_; }
		operator const char*() const { return ptr_; }
		char* ptr(const int idx = 0) { return &ptr_[idx]; }
		const char* ptr(const int idx = 0) const { return &ptr_[idx]; }
		char* next() { return &ptr_[size_]; }
		const char* next() const { return &ptr_[size_]; }
		const char& operator[](const int idx) const { return ptr_[idx]; }
		char* begin() { return ptr_; }
		const char* begin() const { return ptr_; }
		char* end() { return ptr_ + size_; }
		const char* end() const { return ptr_ + size_; }

	private:
		Buffer(const Buffer&) = delete;
		Buffer& operator=(const Buffer&) = delete;
		
		char* ptr_;
		size_t size_;
		size_t capacity_;
	};

	typedef std::shared_ptr<Buffer> buffer_ptr;

	class buffer_reader
	{
	public:
		buffer_reader(const char* buf) : buffer_(buf), offset_(0)
		{
		}

		template <typename T>
		void read(T& val)
		{
			val = (T)(*(T*)(buffer_ + offset_));
			offset_ += sizeof(T);
		}

		void read(char* val, size_t length)
		{
			val = (char*)(buffer_ + offset_);
			offset_ += length;
		}

		void read(char* val)
		{
			val = (char*)(buffer_ + offset_);
			offset_ + sizeof(char); // '\0'
			int len = ::strlen(val);
			if (len > 0) offset_ += len;
			else val = NULL;
		}

		void read(std::string& val)
		{
			char* str = (char*)(buffer_ + offset_);
			offset_ += sizeof(char); // '\0'
			int len = strlen(str);
			if (len > 0)
			{
				offset_ += len;
				val.assign(str);
			}
			else
			{
				val.clear();
			}
		}

		void reset() { offset_ = 0; }
		size_t offset() const { return offset_; }
	private:
		const char* buffer_;
		size_t offset_;
	};

	class buffer_writer
	{
	public:
		buffer_writer(char* buf) : buffer_(buf), offset_(0)
		{
		}
		template <typename T>
		void write(T val)
		{
			::memcpy(buffer_ + offset_, &val, sizeof(T));
			offset_ += sizeof(T);
		}
		void write(const char* val, size_t length)
		{
			::memcpy(buffer_ + offset_, val, length);
			offset_ += length;
		}
		void write(const char* val)
		{
			if (val)
			{
				int len = ::strlen(val);
				::memcpy(buffer_ + offset_, val, len);
				offset_ += len;
			}
			buffer_[offset_] = '\0';
			offset_ += sizeof(char);
		}
		void write(const std::string& val)
		{
			if (!val.empty())
			{
				int len = val.length();
				::memcpy(buffer_ + offset_, val.data(), val.length());
				offset_ += len;
			}
			buffer_[offset_] = '\0';
			offset_ += sizeof(char);
		}
		void reset() { offset_ = 0; }
		size_t offset() const { return offset_; }
	private:
		char* buffer_;
		size_t offset_;
	};
} // reactor