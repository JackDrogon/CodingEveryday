#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
	int ix;
	while (cin >> ix) {
		switch (ix) {
		case 1:
			cout << "u input 1 and break" << endl;
			break;
		case 2:
			cout << "u input 2 and continue" << endl;
			continue;
		default:
			cout << "if continue then default..." << endl;
			break;
		}
		cout << "after switch ix: " << ix << endl;
	}

	return 0;
}
