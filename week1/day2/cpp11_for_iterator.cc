#include <iostream>
#include <vector>
using namespace std;

int main()
{
	vector<int> vec;
	for (int i = 0; i < 10; ++i) vec.push_back(i);
	for (auto &ele: vec) {
		cout << ele << endl;
	}

	return 0;
}
