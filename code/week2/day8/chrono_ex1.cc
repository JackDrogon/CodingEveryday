#include <iostream>
#include <chrono>

int main()
{
	std::chrono::seconds twentySeconds(20);
	std::chrono::hours aDay(24);

	std::chrono::milliseconds ms;
	ms += twentySeconds + aDay;
	--ms;
	ms *= 2;
	std::cout << ms.count() << " ms" << std::endl;
	std::cout << std::chrono::nanoseconds(ms).count() << " ns" << std::endl;

	return 0;
}
