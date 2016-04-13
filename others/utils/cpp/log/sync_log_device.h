#ifndef SYNC_LOG_DEVICE_H_
#define SYNC_LOG_DEVICE_H_

#include "log_device.h"

#include <string>
#include <mutex>

// doc: LogDevice is a basic class, you can implement it by you self
// Flush, Write
// A better idea is use handle as basic class, just need handle to be had method flush && close, open...

class SyncLogDevice: public LogDevice {
public:
	SyncLogDevice(FILE *handle);
	virtual ~SyncLogDevice() override;

	virtual void Append(const std::string &msg) override;
	virtual void Append(const char *msg, const size_t size) override;
	virtual void Flush() override;

private:
	FILE *handle_;
	std::mutex mutex_;
};

#endif // SYNC_LOG_DEVICE_H_
