#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
	int server_sockfd, client_sockfd;
	int server_len, client_len;
	struct sockaddr_in server_address, client_address;

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
		read(client_sockfd, &ch, 1);
		++ch;
		write(client_sockfd, &ch, 1);

		// Step 6 close()
		close(client_sockfd);
	}

	return 0;
}
