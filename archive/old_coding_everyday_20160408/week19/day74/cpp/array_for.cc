#include <array>
#include <iostream>

int main()
{
	std::array<int, 10> a;
	for (int i = 0; i < 10; i++) {
		a[i] = ((i * 32315 ^ 393) & 15);
	}

	for (int v : a)
		std::cout << v << '\n';
}
