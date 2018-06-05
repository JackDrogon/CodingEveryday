#include <iostream>
using namespace std;

int main()
{
	int i = 4, j = 5;

	cout << "Before sizeof, i: " << i << ", j: " << j << endl;
	sizeof(i++);
	sizeof(++j);
	cout << "After sizeof, i: " << i << ", j: " << j << endl;

	return 0;
}
