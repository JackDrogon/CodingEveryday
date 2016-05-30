// Author : Jack Drogon
// Mail   : jack.xsuperman@gmail.com


#ifndef SOCKET_H_
#define SOCKET_H_

#include <memory>
#include <sys/socket.h>

namespace nepenthe {

class InetAddress;

// TODO: right reference
// TODO: noncopy

class Socket {
public:
	explicit Socket(int sockfd) : sockfd_(sockfd) {}
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

	int Write(std::string write_buffer);
	int Write(const char write_buffer[], ssize_t len);
	std::string Read();
	ssize_t ReadN(char *const buf, size_t n);

	int SockFd() const { return sockfd_; }
private:
	const int sockfd_;
};

} // nepenthe

#endif // SOCKET_H_
