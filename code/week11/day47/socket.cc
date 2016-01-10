#include "socket.h"

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

Socket::~Socket() { ::close(sockfd_); }

void Socket::SetTcpNoDelay(bool on)
{
	int optval = on ? 1 : 0;
	::setsockopt(sockfd_, IPPROTO_TCP, TCP_NODELAY, &optval,
		     static_cast<socklen_t>(sizeof optval));
	// FIXME CHECK
}

void Socket::SetReuseAddr(bool on)
{
	int optval = on ? 1 : 0;
	::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEADDR, &optval,
		     static_cast<socklen_t>(sizeof optval));
	// FIXME CHECK
}

void Socket::SetReusePort(bool on)
{
#ifdef SO_REUSEPORT
	int optval = on ? 1 : 0;
	int ret = ::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEPORT, &optval,
			       static_cast<socklen_t>(sizeof optval));
	if (ret < 0 && on) {
		LOG_SYSERR << "SO_REUSEPORT failed.";
	}
#else
	if (on) {
		LOG_ERROR << "SO_REUSEPORT is not supported.";
	}
#endif
}

void Socket::SetKeepAlive(bool on)
{
	int optval = on ? 1 : 0;
	::setsockopt(sockfd_, SOL_SOCKET, SO_KEEPALIVE, &optval,
		     static_cast<socklen_t>(sizeof optval));
	// FIXME CHECK
}
