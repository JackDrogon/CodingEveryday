#ifndef UNIX_SOCKET_H_
#define UNIX_SOCKET_H_

#include <string>
#include <sys/un.h>

class UnixSocket {
public:
	UnixSocket(std::string &sock_path, int type, int protocol);
	UnixSocket(int type, int protocol);
	void Bind();

private:
	std::string sock_path_;
	struct sockaddr_un addr;
	int fd_;
};

#endif // UNIX_SOCKET_H_
