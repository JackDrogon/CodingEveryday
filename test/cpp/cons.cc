#include <iostream>
using namespace std;

class T1 {
public:
	T1() {cout << "Default Construct" << endl;}
	T1(int i ) : i_(i) {cout << "Construct" << endl;}
	T1(string s) {((void) s); cout << "Construct by string" << endl;}
	T1(const T1& t) : i_(t.i_) {cout << "Copy Construct" << endl;}
	~T1() {cout << "Destruct" << endl;}

	int i_;
};

int main()
{
	// 都是只经过一次构造和析构，感觉有点奇怪，最好反汇编看一下
	// T1 t = T1(1);
	// T1(1);
	// T1 t1(T1(1));
	// T1 t1("xx");
	// T1 t2 = "xx"; can't use think...
	
	T1 t = 1;
}
