#ifndef BUFFER_H_
#define BUFFER_H_

#include <string>

// TODO: now it can be replace by string
// TODO: Resize

class Buffer {
public:
	Buffer(size_t capacity = (4 << 10));
	~Buffer();

	char* Data();

	size_t Append(std::string &msg);
	size_t Append(const char* msg);
	size_t Append(const char* msg, const size_t size);

	size_t Capacity();
	size_t Size();
	void Clear();
	size_t Avail();
	bool Full();
	// size_t Resize(size_t size);

private:
	size_t capacity_;
	size_t size_;
	char* buffer_;
};

#endif // BUFFER_H_
