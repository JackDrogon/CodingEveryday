#include "unix_socket.h"

#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>

using std::string;

UnixSocket::UnixSocket(string &sock_path, int type, int protocol)
	: UnixSocket(type, protocol)
{
	sock_path_ = sock_path;
	if (remove(sock_path.data()) == -1 && errno != ENOENT) {
		abort();
	}

	memset(&addr, 0, sizeof(addr));
	
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, sock_path_.data(), sock_path_.length());
}

UnixSocket::UnixSocket(int type, int protocol)
{
	int sock_fd = ::socket(AF_UNIX, type, protocol);
	if (sock_fd == -1) {
		abort();
	}

	fd_ = sock_fd;
}
