#ifndef PIDFILE_H_
#define PIDFILE_H_

#include <fstream> // for ifstream && ofstream
#include <unistd.h> // for getpid && pid_t

// TODO: Add eror handle

void inline pidfile_write(const std::string& filename = "pidfile")
{
	std::ofstream pidfile(filename);
	pidfile << getpid() << std::endl;
}

pid_t inline pidfile_read(const std::string& filename = "pidfile")
{
	std::ifstream pidfile(filename);
	pid_t pid;
	pidfile >> pid;

	return pid;
}

#endif // PIDFILE_H_
