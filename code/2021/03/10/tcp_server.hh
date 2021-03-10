#include <cstdint>
#include <string>

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/write.hpp>

using boost::asio::ip::tcp;

struct TcpServerOption {
	std::string ip;
	uint16_t port;
	uint64_t backlog;
	bool reuseaddr;
	bool reuseport;
};

template <typename Session> class TcpServer {
    public:
	TcpServer(boost::asio::io_context &io_context,
		  const TcpServerOption &opt)
		: acceptor_(io_context,
			    boost::asio::ip::tcp::endpoint(
				    boost::asio::ip::tcp::v4(), opt.port))
	{
		// TODO: update backlog
		accept();
	}
	~TcpServer() = default;

	TcpServer(const TcpServer &) = delete;
	TcpServer(TcpServer &&srv) : acceptor_(std::move(srv.acceptor_))
	{
	}
	TcpServer &operator=(const TcpServer &) = delete;
	TcpServer &operator=(TcpServer &&srv)
	{
		acceptor_ = std::move(srv.acceptor_);
		return *this;
	}

    private:
	void accept()
	{
		acceptor_.async_accept([this](boost::system::error_code ec,
					      tcp::socket socket) {
			if (!ec) {
				std::make_shared<Session>(std::move(socket))
					->Start();
			}

			accept();
		});
	}

    private:
	boost::asio::ip::tcp::acceptor acceptor_;
};
