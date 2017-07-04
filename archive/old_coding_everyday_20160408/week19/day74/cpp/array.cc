#include <array>
#include <algorithm>
#include <iostream>

int main()
{
	const int arraysize = 10;
	std::array<int, arraysize> a;
	for (int i = 0; i < arraysize; i++) {
		a[i] = ((i * 32315 ^ 393) & 15);
	}
	std::for_each(a.begin(), a.end(),
		      [](int v) { std::cout << v << '\n'; });
}
