#include "base64.h"

#include <iostream>
#include <string>
using namespace std;

int main()
{
	// cout << "default_base64_encode_table size: " << sizeof(base64::default_base64_encode_table) << endl;
	string s = "Hello,World!";
	cout << base64::encode(s) << endl;

	cout << base64::encode("foo") << endl;
	cout << base64::encode("H") << endl;
	cout << base64::encode("x") << endl;


	cout << base64::decode("\t       SGVsbG\t     8sV29ybGQh\t=======") << endl;
	cout << base64::decode("SGVsbG8sV29ybGQh") << endl;
}
