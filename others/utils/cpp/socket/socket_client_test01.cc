#include "socket.h"
#include "inet_address.h"

#include <iostream>
#include <netinet/in.h>

using namespace nepenthe::net;
using namespace std;

int main()
{
	Socket client(SOCK_STREAM, 0);
	InetAddress server_address("localhost", 33933);

	client.Connect(server_address);
	auto msg = client.Read();

	cout << msg << flush;
	
	return 0;
}
