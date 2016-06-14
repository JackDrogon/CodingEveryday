#include <string>

namespace nepenthe {

class Server {
private:
	// TODO Function declare
	// using 
public:
	static void udp_server_loop(uint16_t port);
	static void udp_server_loop(std::string ip, uint16_t port);
	static void udp_server_loop(const char *ip, uint16_t port);
};

} // nepenthe
