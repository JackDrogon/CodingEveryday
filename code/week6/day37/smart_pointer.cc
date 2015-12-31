#include <iostream>
#include <memory>

using namespace std;

int main()
{
	shared_ptr<int> p_int = make_shared<int>(42);
	cout << p_int << " => " << *p_int << endl;

	shared_ptr<int> p_int2 = make_shared<int>();

	return 0;
}
