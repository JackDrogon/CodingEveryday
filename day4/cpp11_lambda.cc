#include <iostream>
#include <functional>
using namespace std;

int main()
{
	const char *str = "Hello, World!";
	int uppercase = 0;
	// [capture list](parameter list) -> return_type {function body}
	// parameter list && return_type can be ignore
	for_each(str, str + sizeof(str), [&uppercase](char c){ if (isupper(c)) ++uppercase; });
	cout << uppercase << " uppercase letters in: " << str << endl;

	auto f1 = [] { return 42; };
	cout << f1() << endl;

	auto f2 = [](const string &s1, const string &s2) { return s1.size() < s2.size(); };
	cout << f2("hello", "world") << endl;


	string sz = "hello";
	auto f3 = [sz](const string &s1) { return sz.size() < s1.size(); };
	cout << f3("world") << endl;

	int i = 10;
	// auto f4 = [i]() {i = 5;}; 此处 i是const copy
	auto f5 = [&i]() { i = 5; };
	f5();
	cout << i << endl;

	return 0;
}
