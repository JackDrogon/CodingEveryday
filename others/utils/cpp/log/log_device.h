#ifndef LOG_DEVICE_H_
#define LOG_DEVICE_H_

#include <string>
#include <mutex>


// doc: LogDevice is a basic class, you can implement it by you self
// Flush, Write
// A better idea is use handle as basic class, just need handle to be had method flush && close, open...

class LogDevice {
public:
	LogDevice(FILE *handle, bool sync_write);
	~LogDevice();
	void Write(const std::string &severity, const std::string &now, const std::string &msg);
	void ASyncWrite(const std::string &severity, const std::string &now, const std::string &msg);
	void SyncWrite(const std::string &severity, const std::string &now, const std::string &msg);

	void Flush();
private:
	FILE *handle_;
	bool sync_write_;
	std::mutex mutex_;
};

#endif // LOG_DEVICE_H_
