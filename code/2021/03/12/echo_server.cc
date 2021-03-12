#include <iostream>

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/write.hpp>

#include "tcp_server.hh"
#include <sys/socket.h>
#include <sys/syslimits.h>

using namespace std;

class EchoSession : public std::enable_shared_from_this<EchoSession> {
    public:
	EchoSession(boost::asio::ip::tcp::socket socket)
		: socket_(std::move(socket))
	{
	}

	void Start()
	{
		const auto &&remote_endpoint = socket_.remote_endpoint();
		std::cout << "EchoSession Start {[" << remote_endpoint.address()
			  << "]:" << remote_endpoint.port() << "}" << std::endl;
		read();
	}

    private:
	void read()
	{
		auto self(shared_from_this());
		socket_.async_read_some(boost::asio::buffer(data_, max_length),
					[this,
					 self](boost::system::error_code ec,
					       std::size_t length) {
						if (!ec) {
							write(length);
						}
					});
	}

	void write(std::size_t length)
	{
		auto self(shared_from_this());
		boost::asio::async_write(
			socket_, boost::asio::buffer(data_, length),
			[this, self](boost::system::error_code ec,
				     std::size_t /*length*/) {
				if (!ec) {
					read();
				}
			});
	}

	boost::asio::ip::tcp::socket socket_;
	enum { max_length = 1024 };
	char data_[max_length];
};

int main(int argc, char *argv[])
{
	try {
		if (argc != 2) {
			std::cerr << "Usage: async_tcp_echo_server <port>\n";
			return 1;
		}

		boost::asio::io_context io_context;
		TcpServerOption opt;
		opt.port = std::atoi(argv[1]);

		TcpServer<EchoSession> srv(io_context, opt);

		io_context.run();
	} catch (std::exception &e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}
