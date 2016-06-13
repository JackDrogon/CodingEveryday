#include <iostream>
#include "skiplist.h"

using namespace std;
using namespace nepenthe::data_structure;

int main()
{
	SkipList<string, string> skiplist;

	skiplist.Set("Hello", "World");
	string value;
	cout << skiplist.Get("Hello", value) << ": " << value << endl;
	cout << skiplist.Get("Haha", value) << endl;
	cout << skiplist.Delete("Hello") << endl;
	cout << skiplist.Get("Hello", value) << endl;

	return 0;
}
