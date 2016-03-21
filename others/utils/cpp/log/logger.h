#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>
#include <ctime>

// TODO: Logger singleton && LogDevice shared_ptr
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
// TODO: LogDevice only accept string, Format is by Formatter
// TODO: LogDevice AsyncWrite accpet data to append it's own buffer, use a background thread to write, SyncWrite Write immediately
// TODO: Add logger flush callback


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

class LogDevice;
// TODO:Info with char *
class Logger {
public:
	const static int DEBUG, INFO, WARN, ERROR, FATAL, UNKNOWN;
	const static std::string Severity[];

	Logger(bool sync_write = true);
	Logger(const std::string& filename, bool sync_write = true);
	~Logger();
	void SetLevel(const int level);

	void Flush();
	void Debug(std::string msg);
	void Info(std::string msg);
	void Warn(std::string msg);
	void Error(std::string msg);
	void Fatal(std::string msg);
	void Unknown(std::string msg);

private:
	int level_;
	// LogDevice &log_device_;
	LogDevice *log_device_;

	const std::string BuildOutput(const std::string& severity, std::string& msg);
};
#endif

