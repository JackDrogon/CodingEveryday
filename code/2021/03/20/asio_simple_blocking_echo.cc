#include <cstdint>
#include <iostream>

#include <boost/asio.hpp>

using namespace std;
using boost::asio::ip::tcp;

int main()
{
	uint32_t port = 1080;
	boost::asio::io_context io_context(1);

	tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v6(), port));
	auto socket = acceptor.accept();

	char data[1024];
	for (;;) {
		boost::system::error_code err;
		auto length = socket.read_some(boost::asio::buffer(data), err);
		if (err == boost::asio::error::eof) {
			break;
		} else if (err) {
			throw boost::system::system_error(err);
		}

		boost::asio::write(socket, boost::asio::buffer(data, length));
	}

	return 0;
}
