#include <iostream>
using namespace std;

class Singleton {
	static Singleton singleton;
	int i;
	Singleton(int ii) : i(ii) {}
	Singleton(const Singleton&);
public:
	static Singleton* instance() { return &singleton; }
	int val() const { return i; }
};

Singleton Singleton::singleton(47);

int main()
{
	cout << Singleton::instance()->val() << endl;
	return 0;
}
