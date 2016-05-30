#include "socket.h"
#include "inet_address.h"

#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/errno.h>

namespace nepenthe {


Socket::Socket(int type, int protocol)
	: sockfd_(::socket(AF_INET, type, protocol))
{
}

Socket::~Socket() { ::close(sockfd_); }

int Socket::Close() { return ::close(sockfd_); }

int Socket::Bind(const InetAddress &address)
{
	return ::bind(sockfd_, reinterpret_cast<const struct sockaddr *>(address.SockAddr()), address.Size());
}

int Socket::Connect(const InetAddress &address)
{
	// ::connect(sockfd_, &(const_cast<InetAddress &>(address).SockAddr()), const_cast<InetAddress &>(address).Size());
	return ::connect(sockfd_, reinterpret_cast<const struct sockaddr *>(address.SockAddr()), address.Size());
}


int Socket::Listen(int backlog)
{
	return ::listen(sockfd_, backlog);
}

std::shared_ptr<Socket> Socket::Accept(InetAddress &client_address)
{
	socklen_t addrlen = client_address.Size();
	int client_fd = ::accept(sockfd_, reinterpret_cast<struct sockaddr *>(client_address.SockAddr()), &addrlen);

	if (client_fd < 0) {
		int saved_errno = errno;
		switch (saved_errno) {
			case EAGAIN:
			case ECONNABORTED:
			case EINTR:
			case EPROTO: // ???
			case EPERM:
			case EMFILE: // per-process lmit of open file desctiptor ???
				// expected errors
				errno = saved_errno;
				break;
			case EBADF:
			case EFAULT:
			case EINVAL:
			case ENFILE:
			case ENOBUFS:
			case ENOMEM:
			case ENOTSOCK:
			case EOPNOTSUPP:
				// unexpected errors
				break;
			default:
				break;
		}

		return std::shared_ptr<Socket>();
	}

	return std::make_shared<Socket>(client_fd);
}

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
		// LOG_SYSERR << "SO_REUSEPORT failed.";
		abort();
	}
#else
	if (on) {
		// LOG_ERROR << "SO_REUSEPORT is not supported.";
		abort();
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

int Socket::Write(std::string write_buffer)
{
	return Write(write_buffer.data(), write_buffer.size());
}

std::string Socket::Read()
{
	// TODO: Add error handling
	char buf[4096];
	auto nread = ::read(sockfd_, buf, 4096);
	if (nread <= 0) {
		return std::string();
	} else {
		return std::string(buf);
	}
}

ssize_t Socket::ReadN(char *const buf, size_t n)
{
	size_t nleft;
	ssize_t nread;
	char *ptr;

	ptr = (char*)buf;
	nleft = n;
	while (nleft > 0) {
		if ((nread = read(sockfd_, ptr, nleft)) < 0) {
			if (errno == EINTR)
				nread = 0; /* and call read() again */
			else
				return (-1);
		} else if (nread == 0)
			break; /* EOF */

		nleft -= nread;
		ptr += nread;
	}
	return (n - nleft); /* return >= 0 */
}

int Socket::Write(const char write_buffer[], ssize_t nbytes)
{
	size_t nleft;
	ssize_t nwritten;
	const char *ptr;

	ptr = write_buffer;
	nleft = nbytes;
	while (nleft > 0) {
		if ((nwritten = write(sockfd_, ptr, nleft)) <= 0) {
			if (nwritten < 0 && errno == EINTR)
				nwritten = 0; /* and call write() again */
			else
				return -1; /* error */
		}

		nleft -= nwritten;
		ptr += nwritten;
	}
	return nbytes;
}

} // nepenthe
