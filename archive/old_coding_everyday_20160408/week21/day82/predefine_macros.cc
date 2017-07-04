#include <iostream>
using namespace std;

class Func {
public:
	// function predefine macros
	const char *hello() { return __func__; }
	const char *world() { return __func__; }
	// const char *function { return __FUNCTION__; }
	const char *pretty_func() { return __PRETTY_FUNCTION__; }
	
	// __FILE__
	const char *file() { return __FILE__; }
	// __LINE__
	int line() { return __LINE__; }

	// __DATE__
	const char *date() { return __DATE__; }
	// time
	const char *time() { return __TIME__; }
	const char *timestamp() { return __TIMESTAMP__; }
};

int main()
{
	Func f;

	cout << f.hello() << endl;
	cout << f.world() << endl;
	cout << f.pretty_func() << endl;


	cout << f.file() << endl;
	cout << f.line() << endl;

	cout << f.date() << endl;
	cout << f.time() << endl;
	cout << f.timestamp() << endl;

	return 0;
}
