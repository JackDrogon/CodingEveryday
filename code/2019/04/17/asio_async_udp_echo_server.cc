#include <iostream>
using namespace std;

#include <boost/noncopyable.hpp>

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/udp.hpp>
using boost::asio::ip::udp;

class UDPServer : public boost::noncopyable
{
public:
	UDPServer(boost::asio::io_context &io_context, unsigned short port)
	    : socket_(io_context, udp::endpoint(udp::v4(), port))
	{
	}

	void Start() { read(); }

private:
	void read()
	{
		socket_.async_receive_from(
		    boost::asio::buffer(data_), sender_endpoint_,
		    [this](const boost::system::error_code &ec,
			   size_t recvd_bytes) {
			    if (ec) {
				    read();
			    } else {
				    write(recvd_bytes);
			    }
		    });
	}

	void write(size_t write_bytes)
	{
		socket_.async_send_to(
		    boost::asio::buffer(data_, write_bytes), sender_endpoint_,
		    [this](const boost::system::error_code & /*ec*/,
			   size_t /* sent_bytes */) { read(); });
	}

private:
	static constexpr int kMaxLength = 1024;
	udp::socket socket_;
	udp::endpoint sender_endpoint_;
	char data_[kMaxLength];
};

int main(const int argc, const char *argv[])
{
	if (argc < 2) {
		cerr << argv[0] << " [port]" << endl;
	}

	try {
		boost::asio::io_context io_context(1);
		UDPServer udpserver(io_context, static_cast<unsigned short>(
						    std::atoi(argv[1])));
		udpserver.Start();

		io_context.run();
	} catch (std::exception &e) {
		cerr << "Exception: " << e.what() << endl;
	}

	return 0;
}
