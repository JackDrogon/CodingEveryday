#include <iostream>

#include <boost/asio.hpp>

using namespace std;

using boost::asio::awaitable;
using boost::asio::co_spawn;
using boost::asio::detached;
using boost::asio::use_awaitable;
using boost::asio::ip::tcp;

awaitable<void> echo(tcp::socket socket)
{
	// TODO: error_code handle
	char data[1024];

	for (;;) {
		auto length = co_await socket.async_read_some(
			boost::asio::buffer(data), use_awaitable);

		co_await boost::asio::async_write(
			socket, boost::asio::buffer(data, length),
			use_awaitable);
	}
}

awaitable<void> listener()
{
	auto executor = co_await boost::asio::this_coro::executor;
	tcp::acceptor acceptor(executor, { tcp::v6(), 1080 });

	for (;;) {
		auto socket = co_await acceptor.async_accept(use_awaitable);
		co_spawn(executor, echo(std::move(socket)), detached);
	}
}

int main()
{
	boost::asio::io_context io_context(1);

	boost::asio::signal_set signals(io_context, SIGINT, SIGTERM);
	signals.async_wait([&](auto, auto) { io_context.stop(); });

	co_spawn(io_context, listener(), detached);

	io_context.run();

	return 0;
}
