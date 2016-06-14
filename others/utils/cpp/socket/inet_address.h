// Author : Jack Drogon
// Mail   : jack.xsuperman@gmail.com


#ifndef INET_ADDRESS_H_
#define INET_ADDRESS_H_

#include <string>
#include <cstdint>
#include <sys/socket.h>
#include <netinet/in.h>

namespace nepenthe {

namespace net {

// TODO: deny default cons

class InetAddress {
public:
	InetAddress() = default;
	InetAddress(const struct sockaddr_in &address);
	InetAddress(const std::string &ip, uint16_t port);
	InetAddress(const char *ip, uint16_t port);
	InetAddress(const in_addr_t ip, uint16_t port);

	socklen_t Size() const { return static_cast<socklen_t>(sizeof(address_)); }
	const struct sockaddr_in *SockAddr() const { return &address_; }
	struct sockaddr_in *SockAddr() { return &address_; }

	std::string Ip() const;
	uint16_t Port() const;
	std::string ToString() const;

private:
	struct sockaddr_in address_;
};


} // net

} // nepenthe

#endif // INET_ADDRESS_H_
