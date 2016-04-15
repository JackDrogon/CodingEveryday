#ifndef LOG_DEVICE_H_
#define LOG_DEVICE_H_

#include <string>

// doc: LogDevice is a basic class, you can implement it by you self
// Flush, Write
// A better idea is use handle as basic class, just need handle to be had method flush && close, open...

class LogDevice {
public:
	virtual ~LogDevice() = default;

	virtual void Append(const std::string &msg) = 0;
	virtual void Append(const char *msg, const size_t size) = 0;
	virtual void Flush() = 0;
};


#endif // LOG_DEVICE_H_
