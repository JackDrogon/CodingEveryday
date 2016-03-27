#include <iostream>
#include <functional>
using namespace std;


struct A {
	void hello() { cout << "hello: " << i << endl; }
	int i = 10;
};


int main()
{
	A a;
	a.hello();
	// (&A::hello)(&a);
	function<void()> func = std::bind(&A::hello, &a);
	func();
}
