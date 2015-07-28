#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
	if (numRows == 1 || numRows >= s.size()) return s;

	vector<int> pos;
	int pos_len = 2 * numRows - 2;
	for (int i = 0; i < numRows; ++i) pos.push_back(i);
	for (int i = numRows, j = numRows-1; i < 2*numRows-2; ++i) pos.push_back(--j);

#ifdef TEST
	for (int i = 0; i < pos.size(); ++i) cout << pos[i] << " ";
	cout << endl;
#endif

	vector<string> t(numRows);
	int len = s.length();
	for (int i = 0; i < len; ++i) {
		t[pos[i%pos_len]].push_back(s[i]);
	}

	string result;
	for (int i = 0; i < numRows; ++i) {
		result += t[i];
	}

	return result;
    }
};

int main()
{
	Solution s;
	string str = s.convert("PAYPALISHIRING", 3);
	/* string str = s.convert("A", 1); */
	cout << str << endl;

	return 0;
}
