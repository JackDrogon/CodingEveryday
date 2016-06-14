// Author : Jack Drogon
// Mail   : jack.xsuperman@gmail.com


#include "inet_address.h"

#include <cstring>
#include <cassert>
#include <arpa/inet.h>
// #include <endian.h>

namespace nepenthe {

namespace net {

InetAddress::InetAddress(const struct sockaddr_in &address)
	: address_(address)
{
}

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

std::string InetAddress::Ip() const
{
	const size_t size = 64;
	char buf[size];
	::inet_ntop(AF_INET, &address_.sin_addr, buf, static_cast<socklen_t>(size));

	return buf;
}

uint16_t InetAddress::Port() const
{
	return ntohs(address_.sin_port);
}

std::string InetAddress::ToString() const
{
	auto ip_port = Ip();
	uint16_t port = Port();

	return ip_port.append(":").append(std::to_string(port));
}

} // net

} // nepenthe
