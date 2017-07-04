#include <iostream>
using namespace std;

class T {
public:
	T(int n) : n_(n) { cout << "ctor: " << n_ << endl; }
	~T() { cout << "dtor: " << n_ << endl; }
	int n_;
};

int main(int argc, char *argv[])
{
	T(0);
	cout << "------------" << endl;
	return 0;
}
