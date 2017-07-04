#ifndef SOCKET_H_
#define SOCKET_H_

class Socket {
public:
	explicit Socket(int sockfd) : sockfd_(sockfd) {}
	~Socket();

	void SetTcpNoDelay(bool on);
	void SetReuseAddr(bool on);
	void SetReusePort(bool on);
	void SetKeepAlive(bool on);
private:
	const int sockfd_;
};

#endif // SOCKET_H_
