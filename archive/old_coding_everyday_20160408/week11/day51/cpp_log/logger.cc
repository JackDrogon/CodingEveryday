#include "logger.h"

const int Logger::DEBUG   = 0;
const int Logger::INFO    = 1;
const int Logger::WARN    = 2;
const int Logger::ERROR   = 3;
const int Logger::FATAL   = 4;
const int Logger::UNKNOWN = 5;


const std::string Logger::Severity[] = {"DEBUG", "INFO", "WARN", "ERROR", "FATAL", "UNKNOWN"};

Logger::Logger() : log_device_(stdout) {}

Logger::Logger(const std::string &filename) : log_device_(fopen(filename.c_str(), "ae")) {}

Logger::~Logger() { Flush(); }

// TODO: 防止level的越界
void Logger::SetLevel(const int level)
{
	level_ = level;
}

void Logger::Debug(const std::string& msg)
{
	if (level_ <= DEBUG) {
		log_device_.Write(Severity[DEBUG], msg);
	}
}

void Logger::Info(const std::string& msg)
{
	if (level_ <= INFO) {
		log_device_.Write(Severity[INFO], LogTimeStamp::Now(), msg);
	}
}

void Logger::Warn(const std::string& msg)
{
	if (level_ <= WARN) {
		log_device_.Write(Severity[WARN], msg);
	}
}

void Logger::Error(const std::string& msg)
{
	if (level_ <= ERROR) {
		log_device_.Write(Severity[ERROR], msg);
		Flush();
	}
}

void Logger::Fatal(const std::string& msg)
{
	if (level_ <= FATAL) {
		log_device_.Write(Severity[FATAL], msg);
		Flush();
	}
}

void Logger::Unknown(const std::string& msg)
{
	log_device_.Write(Severity[UNKNOWN], msg);
	Flush();
}

void Logger::Flush()
{
	log_device_.Flush();
}


LogDevice::LogDevice(FILE *handle) : handle_(handle) {}
LogDevice::~LogDevice() { fclose(handle_); }

void LogDevice::Write(const std::string &severity, const std::string &msg)
{
	std::lock_guard<std::mutex> mutex_guard(mutex_);

	fprintf(handle_, "%s, ", severity.data());
	fwrite(msg.data(), 1, msg.size(), handle_);
	fprintf(handle_, "\n");
}

void LogDevice::Write(const std::string &severity, const std::string &now, const std::string &msg)
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
