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


inline const std::string Logger::BuildOutput(const std::string& severity, std::string& msg)
{
	// FIXME: can use iomov
	std::string output;
	char buf[64];
	sprintf(buf, "[%s] %s, ", severity.data(), LogTimeStamp::Now().data());
	output.append(buf).append(msg).append("\n");

	return output;
}

// TODO: 防止level的越界
void Logger::SetLevel(const int level)
{
	level_ = level;
}

void Logger::Debug(std::string msg)
{
	if (level_ <= DEBUG) {
		log_device_->Append(BuildOutput(Severity[DEBUG], msg));
	}
}

void Logger::Info(std::string msg)
{
	if (level_ <= INFO) {
		log_device_->Append(BuildOutput(Severity[INFO], msg));
	}
}

void Logger::Warn(std::string msg)
{
	if (level_ <= WARN) {
		log_device_->Append(BuildOutput(Severity[WARN], msg));
	}
}

void Logger::Error(std::string msg)
{
	if (level_ <= ERROR) {
		log_device_->Append(BuildOutput(Severity[ERROR], msg));
		Flush();
	}
}

void Logger::Fatal(std::string msg)
{
	if (level_ <= FATAL) {
		log_device_->Append(BuildOutput(Severity[FATAL], msg));
		Flush();
	}
}

void Logger::Unknown(std::string msg)
{
	log_device_->Append(BuildOutput(Severity[UNKNOWN], msg));
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
