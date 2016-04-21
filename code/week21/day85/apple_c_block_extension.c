#include <stdio.h>

int main()
{
	int multiplier = 7;

	int (^myBlock)(int) = ^(int num) {
	  return num * multiplier;
	};

	printf("%d\n", myBlock(3));
	return 0;
}
