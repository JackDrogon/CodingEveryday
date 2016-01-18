#include "logger.h"
#include "log_device.h"

const int Logger::DEBUG   = 0;
const int Logger::INFO    = 1;
const int Logger::WARN    = 2;
const int Logger::ERROR   = 3;
const int Logger::FATAL   = 4;
const int Logger::UNKNOWN = 5;


const std::string Logger::Severity[] = {"DEBUG", "INFO", "WARN", "ERROR", "FATAL", "UNKNOWN"};

Logger::Logger(bool sync_write) : log_device_(new LogDevice(stdout, sync_write)) {}

Logger::Logger(const std::string &filename, bool sync_write) : log_device_(new LogDevice(fopen(filename.c_str(), "ae"), sync_write)) {}

Logger::~Logger() { delete log_device_; }

// TODO: 防止level的越界
void Logger::SetLevel(const int level)
{
	level_ = level;
}

void Logger::Debug(const std::string& msg)
{
	if (level_ <= DEBUG) {
		log_device_->Write(Severity[DEBUG], LogTimeStamp::Now(), msg);
	}
}

void Logger::Info(const std::string& msg)
{
	if (level_ <= INFO) {
		log_device_->Write(Severity[INFO], LogTimeStamp::Now(), msg);
	}
}

void Logger::Warn(const std::string& msg)
{
	if (level_ <= WARN) {
		log_device_->Write(Severity[WARN], LogTimeStamp::Now(), msg);
	}
}

void Logger::Error(const std::string& msg)
{
	if (level_ <= ERROR) {
		log_device_->Write(Severity[ERROR], LogTimeStamp::Now(), msg);
		Flush();
	}
}

void Logger::Fatal(const std::string& msg)
{
	if (level_ <= FATAL) {
		log_device_->Write(Severity[FATAL], LogTimeStamp::Now(), msg);
		Flush();
	}
}

void Logger::Unknown(const std::string& msg)
{
	log_device_->Write(Severity[UNKNOWN], LogTimeStamp::Now(), msg);
	Flush();
}

void Logger::Flush()
{
	log_device_->Flush();
}
// Add CPP11 move
const std::string LogTimeStamp::Now()
{
	time_t now;
	char buf[64];

	now = time(NULL);
	// TODO: Change the default time format
	strftime(buf, 64, "%d %b %H:%M:%S", localtime(&now));

	return std::string(buf);
}
