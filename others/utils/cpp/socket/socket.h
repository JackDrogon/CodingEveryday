// Author : Jack Drogon
// Mail   : jack.xsuperman@gmail.com


#pragma once

#include <memory>
#include <sys/socket.h>

namespace nepenthe {

namespace net {

class InetAddress;

// TODO: right reference
// TODO: noncopy

class Socket {
public:
	explicit Socket(int sockfd) : sockfd_(sockfd) {}
	explicit Socket(std::string uri);
	Socket(int type, int protocol);
	~Socket();

	void SetTcpNoDelay(bool on);
	void SetReuseAddr(bool on);
	void SetReusePort(bool on);
	void SetKeepAlive(bool on);

	int Close();
	int Connect(const InetAddress &address);
	int Bind(const InetAddress &address);
	int Listen(int backlog = SOMAXCONN);
	std::shared_ptr<Socket> Accept(InetAddress &client_address);

	std::string Read();
	ssize_t Readn(char *const buf, size_t n);
	ssize_t Readv(const struct iovec *iov, int iovcnt);

	int Write(std::string write_buffer);
	int Write(const char write_buffer[], ssize_t len);
	ssize_t Writev(const struct iovec *iov, int iovcnt);

	int SockFd() const { return sockfd_; }

private:
	const int sockfd_;
};

} // net

} // nepenthe
