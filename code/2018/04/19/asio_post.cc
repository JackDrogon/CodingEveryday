#include <iostream>
#include <functional>
#include <boost/asio.hpp>
using namespace std;
using namespace boost::asio;

io_context context;

void func(int i) { std::cout << "func called, i= " << i << std::endl; }

void run_post()
{
	for (int i = 0; i < 10; i += 2) {
		context.post(bind(func, i + 1));
	}
}

int main(int argc, char *argv[])
{
	context.post(run_post);
	context.run();
}
