#ifndef BUFFER_H_
#define BUFFER_H_

#include <string>

// TODO: now it can be replace by string
// TODO: Resize

class Buffer {
public:
	Buffer(int capacity = (4 << 10));
	~Buffer();

	char* Data();

	int Append(std::string &msg);
	int Append(const char* msg);
	int Append(const char* msg, const int size);

	int Capacity();
	int Size();
	void Clear();
	int Avail();
	bool Full();
	// int Resize(int size);

private:
	int capacity_;
	int size_;
	char* buffer_;
};

#endif // BUFFER_H_
