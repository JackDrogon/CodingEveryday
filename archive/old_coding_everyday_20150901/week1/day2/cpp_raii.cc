#include <iostream>
using namespace std;

class A {
public:
	A()
	{
		cout << "Create A!" << endl;
	}
	~A() 
	{
		cout << "Destory A!" << endl;
	}
};

int main()
{
	{
		A a;
	}

	cout << "Before return!" << endl;

	return 0;
}
