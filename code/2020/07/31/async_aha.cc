#include <iostream>
#include <chrono>
#include <random>
#include <thread>
#include <future>
using namespace std;

namespace
{
static int run(char c)
{
	default_random_engine dre(static_cast<unsigned int>(c));
	uniform_int_distribution<int> id(2, 30);

	for (auto i = 0; i < 10; ++i) {
		this_thread::sleep_for(chrono::milliseconds(id(dre)));
		cout.put(c).flush();
	}

	return static_cast<int>(c);
}

int f1()
{
	return run('.');
}

int f2()
{
	return run('+');
}
} // namespace

int main()
{
	cout << "starting f1() '.' in background"
	     << " and f2() '+' in foreground:" << endl;

	auto result1_future = async(f1);
	auto result2 = f2();

	auto result = result1_future.get() + result2;

	cout << "\nresult of f1() + f2(): " << result << endl;

	return 0;
}
