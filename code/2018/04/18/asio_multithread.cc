#include <iostream>
#include <thread>
#include <atomic>
#include <memory>
#include <vector>
#include <boost/asio.hpp>
using namespace std;

boost::asio::io_context io_context;
atomic_int cnt = 0;

void worker_fun()
{
	cout << ++cnt << '\n';
	io_context.run();
	cout << "End.\n";
}

int main()
{
	auto worker = make_shared<boost::asio::io_context::work>(io_context);
	cout << "Press ENTER key to quit!" << endl;

	vector<thread> threads;
	for (int i = 0; i < 5; ++i) {
		threads.emplace_back(thread(worker_fun));
	}
	cin.get();
	io_context.stop();

	for (int i = 0; i < 5; ++i) {
		threads[i].join();
	}

	return 0;
}
