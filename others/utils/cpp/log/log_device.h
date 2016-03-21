#ifndef LOG_DEVICE_H_
#define LOG_DEVICE_H_

#include <string>
#include <mutex>

class Buffer;

// doc: LogDevice is a basic class, you can implement it by you self
// Flush, Write
// A better idea is use handle as basic class, just need handle to be had method flush && close, open...

class LogDevice {
public:
	LogDevice(FILE *handle, bool sync_write);
	~LogDevice();
	void Append(const std::string &msg);
	void ASyncWrite(const std::string &msg);
	void SyncWrite(const std::string &msg);

	void Flush();

private:
	void ASyncWriteAppend(const char* msg, const int size);

	static const int BUFFER_SIZE;

	FILE *handle_;
	bool sync_write_;
	std::mutex mutex_;

	Buffer* current_buffer_;
	Buffer* next_buffer_;
};

#endif // LOG_DEVICE_H_
