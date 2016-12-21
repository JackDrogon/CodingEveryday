#include <iostream>
using namespace std;

struct T {
	T() { cout << "T ctor" << endl; }
	~T() { cout << "T dtor" << endl; }
};

struct C {
	C(T *t) : t_(t) {cout << "C Add T" << endl;}
	~C() { cout << "Delete T" << endl; delete t_; }
private:
	T *t_;
};

void func(C c1, C c2)
{
}

int main()
{
	func(C(new T()), C(new T()));
}
