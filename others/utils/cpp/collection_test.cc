#include <iostream>
#include <vector>
#include "collection.h"

using namespace std;

void print(int elem) { cout << elem << ' '; }

// simple function object that prints the passed argument
class PrintInt
{
public:
	void operator()(int elem) const { cout << elem << ' '; }
};

int main()
{
	vector<int> coll;

	// insert elements from 1 to 9
	for (int i = 1; i <= 9; ++i) {
		coll.push_back(i);
	}

	// ----------- 1 -------------
	// print all elements
	Collection::foreach(coll, print);		     // operation
	cout << endl;


	// ----------- 2 -------------
	// print all elements
	Collection::foreach(coll, PrintInt());		     // operation
	cout << endl;

	// ----------- 3 -------------
	// print all elements
	Collection::foreach(coll, [](int elem){cout << elem << ' ';});		     // operation
	cout << endl;

	return 0;
}
