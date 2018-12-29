#include "buffer.h"

#include <cstdlib>
#include <cstring>

Buffer::Buffer(size_t capacity) :
	capacity_(capacity),
	size_(0)
	// buffer_(new char[static_cast<size_t>(capacity)])
{
	buffer_ = static_cast<char *>(malloc(sizeof(char) * capacity));
	if (buffer_ == nullptr) {
		capacity = 0;
	}
}

Buffer::~Buffer()
{
	delete[] buffer_;
}

char *Buffer::Data()
{
	return buffer_;
}

size_t Buffer::Append(std::string& msg)
{
	return Append(msg.data(), msg.size());
}

size_t Buffer::Append(const char* msg)
{
	return Append(msg, strlen(msg));
}

size_t Buffer::Append(const char* msg, const size_t size)
{
	if (Full()) return 0;

	// FIXME: Compile warning size_type
	size_t len = (capacity_-size_) < size ? capacity_-size_ : size;
	memcpy(buffer_+size_, msg, len);
	size_ += len;

	return len;
}

void Buffer::Clear()
{
	size_ = 0;
}

size_t Buffer::Capacity()
{
	return capacity_;
}

size_t Buffer::Size()
{
	return size_;
}

bool Buffer::Full()
{
	return capacity_ == size_;
}

size_t Buffer::Avail()
{
	return capacity_ - size_;
}
