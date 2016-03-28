#include <vector>
#include <tuple>
#include <iostream>

typedef std::tuple<int, int, int> i3tuple;

int main()
{
	std::vector<i3tuple> v;
	for (int i = 0; i < 10; i++) {
		v.push_back(i3tuple(i, i * 2, i * 2 + 1));
	}

	for (i3tuple t : v) {
		std::cout << std::get<0>(t) << ' ';
		std::cout << std::get<1>(t) << ' ';
		std::cout << std::get<2>(t) << '\n';
	};
}
