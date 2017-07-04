#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

int main(int argc, char *argv[])
{
	int sockfd;
	int len;
	struct sockaddr_un address;
	int result;

	char ch = 'A';

	// Step 1 socket()
	sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
	address.sun_family = AF_UNIX;
	strcpy(address.sun_path, "server_socket");
	len = sizeof address;

	// Step 2 connect()
	result = connect(sockfd, (struct sockaddr*)&address, len);
	if (result == -1) {
		fprintf(stderr, "%s\n", "oops: client1");
		exit(1);
	}

	// Step 3 do_something
	write(sockfd, &ch, 1);
	read(sockfd, &ch, 1);
	printf("char from server = %c\n", ch);

	// Step 4 close()
	close(sockfd);

	return 0;
}
