#include "sync_log_device.h"

#define fwrite_unlocked fwrite

SyncLogDevice::SyncLogDevice(FILE *handle) :
	handle_(handle),
	mutex_()
{ }

SyncLogDevice::~SyncLogDevice()
{
	Flush();
	fclose(handle_);
}

void SyncLogDevice::Append(const std::string &msg)
{
	Append(msg.data(), msg.size());
}

void SyncLogDevice::Append(const char *msg, const size_t size)
{
	// TODO: funlocked
	std::lock_guard<std::mutex> mutex_guard(mutex_);
	fwrite_unlocked(msg, 1, size, handle_);
}

void SyncLogDevice::Flush()
{
	fflush(handle_);
}
