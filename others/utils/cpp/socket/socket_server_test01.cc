#include "socket.h"
#include "inet_address.h"

#include <iostream>
#include <netinet/in.h>

using namespace nepenthe::net;
using namespace std;

int main()
{
	Socket server(SOCK_STREAM, 0);
	InetAddress address(htonl(INADDR_ANY), 33933);

	cout << "Bind on 33933" << endl;
	
	server.Bind(address);
	server.Listen();
	
	while (true) {
		InetAddress client_address{};
		auto client = server.Accept(client_address);
		if (client.get() == nullptr) {
			break;
		} else {
			cout << "Accept a new connection, from " << client_address.ToString() << endl;
		}

		client->Write("Hello, Morning!\n");
	}

	return 0;
}
