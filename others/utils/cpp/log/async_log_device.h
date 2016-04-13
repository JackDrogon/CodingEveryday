#ifndef ASYNC_LOG_DEVICE_H_
#define ASYNC_LOG_DEVICE_H_

#include "log_device.h"

#include <string>
#include <stack>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

class Buffer;

// doc: AsyncLogDevice is a basic class, you can implement it by you self
// Append
// A better idea is use handle as basic class, just need handle to be had method flush && close, open...

class AsyncLogDevice : public LogDevice {
public:
	AsyncLogDevice(FILE *handle);
	virtual ~AsyncLogDevice() override;

	virtual void Append(const std::string &msg) override;
	virtual void Append(const char *msg, const size_t size) override;
	virtual void Flush() override;

private:
	void write_file_();

	static const int BUFFER_SIZE;

	FILE *handle_;
	std::mutex mutex_;

	Buffer* current_buffer_;
	Buffer* next_buffer_;
	std::stack<Buffer *> empty_buffers_;
	std::queue<Buffer *> write_buffers_;

	std::mutex write_mutex_;
	std::condition_variable write_condv_;
	bool thread_quit_;
	std::thread write_worker_;
};

#endif // ASYNC_LOG_DEVICE_H_
