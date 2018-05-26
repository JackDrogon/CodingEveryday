#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

int main(int argc, char *argv[])
{
	int server_sockfd, client_sockfd;
	int server_len, client_len;
	struct sockaddr_un server_address, client_address;

	unlink("server_socket");

	// Step 1 socket()
	server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

	server_address.sun_family = AF_UNIX;
	strcpy(server_address.sun_path, "server_socket");
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
