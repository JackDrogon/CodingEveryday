#include <iostream>
#include <memory>
#include <functional>
using namespace std;

int main()
{
	shared_ptr<int> s1(new int(10));
	shared_ptr<int> s2(s1);
	cout << s1.use_count() << endl;
}
