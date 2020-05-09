#include "lru.h"

#include <iostream>
#include <string>
using namespace std;

int main()
{
	nepenthe::data_structure::LRU<std::string, int> lru(10);
	lru.put("a", 1);
	lru.put("b", 2);
	lru.put("c", 3);
	cout << lru << endl;

	return 0;
}
