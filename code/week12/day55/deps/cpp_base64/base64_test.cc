#include "base64.h"

#include <iostream>
#include <string>
using namespace std;

int main()
{
	string s = "Hello,World!";
	cout << base64::encode(s) << endl;

	cout << base64::encode("foo") << endl;
	cout << base64::encode("H") << endl;
	cout << base64::encode("x") << endl;
}
