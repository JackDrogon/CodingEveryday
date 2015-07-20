#include <iostream>
using namespace std;

#define X_INT_MAX 2147483647
#define X_INT_MIN (-X_INT_MAX - 1)

class Solution {
public:
    int reverse(int x) {
	if (x == 0) return 0;
	int result = 0;
	int n;
	while (x) {
		n = x % 10;
		if (result > X_INT_MAX/10 || result < X_INT_MIN/10) return 0;
		result = result * 10 + n;
		x /= 10;
	}

	return result;
    }
};

int main()
{
	Solution s;
	cout << s.reverse(123) << endl;
	cout << s.reverse(-123) << endl;
	cout << s.reverse(1534236469) << endl;
	cout << s.reverse(-2147483648) << endl;
}
