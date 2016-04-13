#include "buffer.h"

#include <cstdlib>
#include <cstring>

Buffer::Buffer(int capacity) :
	capacity_(capacity),
	size_(0)
	// buffer_(new char[static_cast<size_t>(capacity)])
{
	buffer_ = reinterpret_cast<char *>(malloc(sizeof(char) * capacity));
	if (buffer_ == NULL) {
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

int Buffer::Append(std::string& msg)
{
	return Append(msg.data(), msg.size());
}

int Buffer::Append(const char* msg)
{
	return Append(msg, strlen(msg));
}

int Buffer::Append(const char* msg, const int size)
{
	if (Full()) return 0;

	// FIXME: Compile warning size_type
	int len = (capacity_-size_) < size ? capacity_-size_ : size;
	memcpy(buffer_+size_, msg, len);
	size_ += len;

	return len;
}

void Buffer::Clear()
{
	size_ = 0;
}

int Buffer::Capacity()
{
	return capacity_;
}

int Buffer::Size()
{
	return size_;
}

bool Buffer::Full()
{
	return capacity_ == size_;
}

int Buffer::Avail()
{
	return capacity_ - size_;
}
