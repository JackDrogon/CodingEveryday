#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
	string result = s;
	int len = s.length();
	for (int i = 0; i < len; ++i) {
		int div = i / (2*numRows-2);
		int rem = i % (2*numRows-2);
		int pos = 0;
		if (rem < numRows) {
			t[rem].push_back(s[i]);
		} else {
			t[rem-numRow].
		}
	}
    }
};

int main()
{
	Solution s;
	string str = s.convert("PAYPALISHIRING", 3);
	cout << str << endl;

	return 0;
}
