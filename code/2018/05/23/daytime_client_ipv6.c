#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> // sockeaddr_in

#define MAXLINE 1024

int main(int argc, char *argv[])
{
	int sockfd;
	unsigned int len;
	struct sockaddr_in6 address;
	int result;
	char recvline[MAXLINE + 1];
	int readn;

	if (argc < 3) {
		fprintf(stderr, "%s hostname port", argv[0]);
	}

	char *ip_address = argv[1];
	int port = atoi(argv[2]);

	// Step 1 socket()
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	memset(&address, 0, sizeof(address));
	address.sin6_family = AF_INET6;
	inet_pton(AF_INET6, ip_address, &address.sin6_addr);
	address.sin6_port = htons(port);

	len = sizeof address;

	// Step 2 connect()
	result = connect(sockfd, (struct sockaddr *)&address, len);
	if (result == -1) {
		fprintf(stderr, "%s\n", "oops: client1");
		exit(1);
	}

	// Step 3 do_something
	while ((readn = read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[readn] = 0;
		if (fputs(recvline, stdout) == EOF) {
			fprintf(stderr, "fputs errror");
			return EXIT_FAILURE;
		}
	}
	if (readn < 0) {
		fprintf(stderr, "read errror");
		return EXIT_FAILURE;
	}

	// Step 4 close()
	close(sockfd);

	return 0;
}
