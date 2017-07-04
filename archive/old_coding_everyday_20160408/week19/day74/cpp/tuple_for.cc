#include <tuple>
#include <iostream>

int main()
{
	auto t = std::make_tuple("String", 5.2, 1);
	std::cout << std::get<0>(t) << ' ' << std::get<1>(t) << ' '
		  << std::get<2>(t) << '\n';
}
