#include "inet_address.h"

#include <cstring>
#include <arpa/inet.h>
// #include <endian.h>

namespace nepenthe {

InetAddress::InetAddress(const std::string &ip, uint16_t port)
	: InetAddress(ip.c_str(), port)
{
}

InetAddress::InetAddress(const char *ip, uint16_t port)
{
	memset(&address_, '\0', sizeof(address_));
	address_.sin_family = AF_INET;
	// FIXME: Error Handling
	::inet_pton(AF_INET, ip, &address_.sin_addr);
	address_.sin_port = htons(port);
}

InetAddress::InetAddress(const in_addr_t ip, uint16_t port)
{
	memset(&address_, '\0', sizeof(address_));
	address_.sin_family = AF_INET;
	address_.sin_addr.s_addr = ip;
	address_.sin_port = htons(port);
}

} // nepenthe
