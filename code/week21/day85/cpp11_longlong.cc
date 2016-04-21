#include <iostream>
#include <climits>
using namespace std;

int main()
{
	long long ll_min = LLONG_MIN;
	long long ll_max = LLONG_MAX;

	unsigned long long ull_max = ULLONG_MAX;

	cout << "min of long long: " << std::hex << ll_min << endl;
	cout << "max of long long: " << std::hex << ll_max << endl;
	cout << "max of unsigned long long: " << std::hex << ull_max << endl;

	return 0;
}
