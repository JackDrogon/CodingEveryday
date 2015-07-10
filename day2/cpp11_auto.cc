#include <iostream>
#include <vector>
using namespace std;

struct Test {
	int a;
	int b;
};

int main()
{
	Test test1 = {.a = 10, .b = 20};
	auto test2 = test1;

	cout << "Test:    a => " << test1.a << ", b => " << test2.b << endl;
	
	vector<int> vec;
	for (int i = 0; i < 10; ++i) vec.push_back(i);

	cout << "Print vec elements: ";
	// beg's type is vector<int>::const_iterator
	for (auto beg = vec.begin(); beg != vec.end(); ++beg)  cout << *beg << " ";
	cout << endl;

	return 0;
}
