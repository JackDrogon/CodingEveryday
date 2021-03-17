#include <cstdint>
#include <string>
#include <functional>

#include <sys/socket.h>
#include <sys/types.h>

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/signal_set.hpp>

struct TcpServerOption {
	std::string ip{ "127.0.0.1" };
	uint16_t port{ 1080 };
	uint64_t backlog{ 1024 };
	bool reuseaddr{ false };
	bool reuseport{ false };

	bool valid() const
	{
		// FIXME
		return true;
	}
};

class TcpServer {
	using startSessionFunc =
		std::function<void(boost::asio::ip::tcp::socket &&)>;

    public:
	TcpServer(boost::asio::io_context &io_context,
		  startSessionFunc start_session, const TcpServerOption &opt)
		: start_session_(std::move(start_session)),
		  signals_(io_context, SIGINT, SIGTERM), acceptor_(io_context)
	{
		signals_.async_wait([&](boost::system::error_code /*ec*/,
					int /*signo*/) { io_context.stop(); });

		initAcceptor(opt);
	}
	~TcpServer() = default;

	TcpServer(const TcpServer &) = delete;
	TcpServer &operator=(const TcpServer &) = delete;

    private:
	// TODO: move to TcpServerBase, reduce template class size
	// icache friendly
	void initAcceptor(const TcpServerOption &opt)
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

	void accept()
	{
		acceptor_.async_accept(
			[this](boost::system::error_code ec,
			       boost::asio::ip::tcp::socket &&socket) {
				if (!ec) {
					start_session_(std::move(socket));
				}

				accept();
			});
	}

    private:
	startSessionFunc start_session_;
	boost::asio::signal_set signals_;
	boost::asio::ip::tcp::acceptor acceptor_;
};
