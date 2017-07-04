#include <iostream>
#include <chrono>
#include <thread>

// constexpr chrono::seconds operator"" s(unsigned long long __s)
// {
	// return chrono::seconds(static_cast<chrono::seconds::rep>(__s));
// }

int main()
{
	using namespace std::literals;

	std::cout << "Hello waiter" << std::endl;
	auto start = std::chrono::high_resolution_clock::now();
	// std::this_thread::sleep_for(std::chrono::seconds(1));
	std::this_thread::sleep_for(1.2s); // by using std::literals, 研究一下, 类似还有bind的_1
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed = end - start;
	std::cout << "Waited " << elapsed.count() << " ms\n";

	return 0;
}
