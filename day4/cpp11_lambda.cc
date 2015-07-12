#include <iostream>
#include <functional>
using namespace std;

int main()
{
	const char *str = "Hello, World!";
	int uppercase = 0;
	// [capture](parameters)->return_type {body}
	for_each(str, str + sizeof(str), [&uppercase](char c){ if (isupper(c)) ++uppercase; });
	cout << uppercase << " uppercase letters in: " << str << endl;

	return 0;
}
