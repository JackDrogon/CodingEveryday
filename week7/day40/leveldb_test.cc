#include <iostream>

#include "leveldb.h"

using namespace std;

int main()
{
	LevelDB db("/tmp/testdb");
	db.Put("Hello", "LevdlDB");
	string value;
	db.Get("Hello", value);
	cout << value << endl;

	return 0;
}
