#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAXLINE 1024

/* Write "n" bytes to a descriptor. */
ssize_t writen(int fd, const void *vptr, size_t nbytes)
{
	size_t nleft;
	ssize_t nwritten;
	const char *ptr;

	ptr = (const char *)vptr;
	nleft = nbytes;
	while (nleft > 0) {
		if ((nwritten = write(fd, ptr, nleft)) <= 0) {
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

int main(int argc, char *argv[])
{
	int server_sockfd, client_sockfd;
	int server_len, client_len;
	struct sockaddr_in server_address, client_address;
	char buf[MAXLINE];

	// Step 1 socket()
	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(33933);

	server_len = sizeof server_address;

	// Step 2 bind()
	bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

	// Step 3 listen()
	listen(server_sockfd, 5);

	// Loop
	while (1) {
		char ch;
		printf("server waiting\n");

		client_len = sizeof client_address;

		// Step 4 accept()
		client_sockfd =
		    accept(server_sockfd, (struct sockaddr *)&client_address,
			   &client_len);

		// Step 5 do_something
		time_t ticks = time(NULL);
		int nbytes =
		    snprintf(buf, sizeof(buf), "%.24s\r\n", ctime(&ticks));
		writen(client_sockfd, buf, nbytes);

		// Step 6 close()
		close(client_sockfd);
	}

	return 0;
}
