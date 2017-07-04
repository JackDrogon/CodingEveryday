#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>
#include <mutex>
#include <ctime>

// TODO: use LogDevice as basic class, add FileDevice...
// Refer to log4j, glog, log4c, log4cpp, log4erl, muduo log, log4r
// TODO: Think about __FILE__, __LINE__, __PROGRAM__
// FIXME: Add format time
// FIXME: Add noncopy
// TODO: Move LogDevice, LogTimeStamp to Logger class inner
// TODO: Think about add namespace
// FIXME: Use logdeive only output, it don't kown, how to format data
// TODO: Add rollback, shiftsize, fixed length file....
// TODO: Add async write
// TODO: Add Thread id, or thread name

class LogDevice {
public:
	LogDevice(FILE *handle);
	~LogDevice();
	void Write(const std::string &severity, const std::string &msg);
	void Write(const std::string &severity, const std::string &now, const std::string &msg);

	void Flush();
private:
	FILE *handle_;
	std::mutex mutex_;
};

class LogTimeStamp {
public:
	static const std::string Now();
};


/*
 * +UNKNOWN+:: An unknown message that should always be logged.
 * +FATAL+:: An unhandleable error that results in a program crash.
 * +ERROR+:: A handleable error condition.
 * +WARN+::  A warning.
 * +INFO+::  Generic (useful) information about system operation.
 * +DEBUG+:: Low-level information for developers.
 *
 * DEBUG < INFO < WARN < ERROR < FATAL < UNKNOWN
 */

// TODO:Info with char *
class Logger {
public:
	const static int DEBUG, INFO, WARN, ERROR, FATAL, UNKNOWN;
	const static std::string Severity[];

	Logger();
	Logger(const std::string& filename);
	~Logger();
	void SetLevel(const int level);

	void Flush();
	void Debug(const std::string& msg);
	void Info(const std::string& msg);
	void Warn(const std::string& msg);
	void Error(const std::string& msg);
	void Fatal(const std::string& msg);
	void Unknown(const std::string& msg);

private:
	int level_;
	LogDevice log_device_;
};
#endif

