#include <cstdint>
#include <string>

#include <sys/socket.h>
#include <sys/types.h> /* See NOTES */

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>

struct TcpServerOption {
	std::string ip{ "127.0.0.1" };
	uint16_t port;
	uint64_t backlog{ 1024 };
	bool reuseaddr{ false };
	bool reuseport{ false };

	bool valid() const
	{
		// FIXME
		return true;
	}
};

template <typename Session> class TcpServer {
    public:
	TcpServer(boost::asio::io_context &io_context,
		  const TcpServerOption &opt)
		: acceptor_(io_context)
	{
		auto endpoint = boost::asio::ip::tcp::endpoint(
			boost::asio::ip::tcp::v6(), opt.port);

		acceptor_.open(endpoint.protocol());
		if (opt.reuseaddr) {
			acceptor_.set_option(
				boost::asio::ip::tcp::acceptor::reuse_address(
					true));
		}
		acceptor_.bind(endpoint);

#if __linux__
		//  set defer accept
		//  NOTE: there is no way to find out how long a connection was
		//  	  in queue (and a connection may bypass deferred queue at all
		//  	  if syncookies were used), hence we use 1 second timeout
		//  	  here.
		auto fd = acceptor_.native_handle();
		int value = 1;
		int rc = setsockopt(fd, IPPROTO_TCP, TCP_DEFER_ACCEPT, &value,
				    sizeof(int));
		if (rc == -1) {
			// FIXME
			// WARN("failed to set TCP_DEFER_ACCEPT for fd {} : {}",
			//      fd, strerror(errno));
		}
#endif

		acceptor_.listen(opt.backlog);
		//                ^^^ if the backlog argument is greater than the
		// 				  value in /proc/sys/net/core/somaxconn, then it is
		//                silently truncated to that value.
		//                so the real backlog is std::min(1024, /proc/sys/net/core/somaxconn)

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
		acceptor_.async_accept(
			[this](boost::system::error_code ec,
			       boost::asio::ip::tcp::socket socket) {
				if (!ec) {
					std::make_shared<Session>(
						std::move(socket))
						->Start();
				}

				accept();
			});
	}

    private:
	boost::asio::ip::tcp::acceptor acceptor_;
};
