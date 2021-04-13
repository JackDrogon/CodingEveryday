#include <iostream>
using namespace std;

int main()
{
	auto str = std::to_string(42);
	auto wstr = std::to_wstring(2137LL);

	cout << str << endl;
	wcout << wstr << endl;

	return 0;
}
