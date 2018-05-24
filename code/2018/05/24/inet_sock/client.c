#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> // sockeaddr_in

int main()
{
	int sockfd;
	unsigned int len;
	struct sockaddr_in address;
	int result;

	char ch = 'A';

	// Step 1 socket()
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	// address.sin_addr.s_addr = inet_addr("127.0.0.1");  deprated
	inet_pton(AF_INET, "127.0.0.1", &address.sin_addr);
	address.sin_port = htons(33933);

	len = sizeof address;

	// Step 2 connect()
	result = connect(sockfd, (struct sockaddr *)&address, len);
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
