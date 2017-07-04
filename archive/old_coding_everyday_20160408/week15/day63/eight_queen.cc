#include <iostream>
using namespace std;

static int sum = 0;
const int MAX = 8;

void print(int board[])
{
	for (int i = 0; i < MAX; i++) {
		cout << board[i] + 1 << "  ";
	}
	cout << endl;
	sum++;
}

bool judge(int board[], int x)
{
	for (int i = 0; i < x; i++) {
		if (board[i] == board[x] ||
		    abs(board[i] - board[x]) == (x - i)) {
			return false;
		}
	}
	return true;
}

void queen(int board[], int x)
{
	if (x == MAX) {
		print(board);
		return;
	}
	for (int i = 0; i < MAX; i++) {
		board[x] = i;
		if (judge(board, x)) {
			queen(board, x + 1);
		}
	}
}
int main()
{
	int board[MAX];
	queen(board, 0);
	cout << "total is " << sum << endl;;
	return 0;
}
