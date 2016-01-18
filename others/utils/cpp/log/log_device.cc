#include "log_device.h"

LogDevice::LogDevice(FILE *handle, bool sync_write) : handle_(handle), sync_write_(sync_write) {}

LogDevice::~LogDevice()
{
	Flush();
	fclose(handle_);
}

void LogDevice::Write(const std::string &severity, const std::string &now, const std::string &msg)
{
	if (sync_write_) {
		SyncWrite(severity, now, msg);
	} else {
		ASyncWrite(severity, now, msg);
	}
}


void LogDevice::ASyncWrite(const std::string &severity, const std::string &now, const std::string &msg)
{
}

void LogDevice::SyncWrite(const std::string &severity, const std::string &now, const std::string &msg)
{
	std::lock_guard<std::mutex> mutex_guard(mutex_);

	fprintf(handle_, "[%s] %s, ", severity.data(), now.data());
	fwrite(msg.data(), 1, msg.size(), handle_);
	fprintf(handle_, "\n");
}


void LogDevice::Flush()
{
	fflush(handle_);
}
