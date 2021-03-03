#include <concepts>
#include <iostream>
using namespace std;

template <typename T>
requires Integral<T>()
T gcd(T a, T b)
{
	if (b == 0) {
		return a;
	} else {
		return gcd(b, a % b);
	}
}

int main(void)
{
	cout << gcd(1000, 2520) << endl;
	return 0;
}
