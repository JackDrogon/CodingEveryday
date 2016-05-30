#include <stdio.h>

struct T1 {
	int len;
	char buf[0];
};

struct T2 {
	int len;
	char buf[1];
};

int main()
{
	printf("sizeof T1: %d\n", sizeof(struct T1));
	printf("sizeof T2: %d\n", sizeof(struct T2));
}
