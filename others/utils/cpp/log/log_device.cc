#include "log_device.h"

#include "buffer.h"

#define fwrite_unlocked fwrite

const int LogDevice::BUFFER_SIZE = 4 << 20;

LogDevice::LogDevice(FILE *handle, bool sync_write) :
	handle_(handle),
	sync_write_(sync_write),
	current_buffer_(nullptr),
	next_buffer_(nullptr)
{
	if (!sync_write_) {
		current_buffer_ = new Buffer(BUFFER_SIZE);
		next_buffer_ = new Buffer(BUFFER_SIZE);
	}
}

LogDevice::~LogDevice()
{
	Flush();
	fclose(handle_);
}

void LogDevice::Append(const std::string &msg)
{
	if (sync_write_) {
		SyncWrite(msg);
	} else {
		ASyncWrite(msg);
	}
}


void LogDevice::ASyncWrite(const std::string &msg)
{
	std::lock_guard<std::mutex> mutex_guard(mutex_);
}

void LogDevice::ASyncWriteAppend(const char* msg, const int size)
{
	if (current_buffer_->Avail() > size) {
		current_buffer_->Append(msg, size);
	}
}

void LogDevice::SyncWrite(const std::string &msg)
{
	std::lock_guard<std::mutex> mutex_guard(mutex_);

	// TODO: funlocked
	fwrite_unlocked(msg.data(), 1, msg.size(), handle_);
}


void LogDevice::Flush()
{
	fflush(handle_);
}
