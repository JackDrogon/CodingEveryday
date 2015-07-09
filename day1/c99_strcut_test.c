#include <stdio.h>

struct A {
	int a;
	int b;
} a = {.a = 1, .b = 2};

void print_a(struct A *a)
{
	printf("Struct A Elements: \n"
		".a => %d\n"
		".b => %d\n",
		a->a, a->b);
}

int main()
{
	print_a(&a);
	// a = {.a = 2}; // Error, 这个只能在初始化的时候使用
	a = (struct A){.a = 2};
	print_a(&a);

	return 0;
}
