#include <stdio.h>

void insert_sort(int* L, int size) {
	int tmp, i, j;
	for (i = 1; i < size; ++i) {
		tmp = L[i];
		for (j = i-1; j >= 0 && L[j] > tmp; --j) {
			L[j+1] = L[j];
		}
		L[j+1] = tmp;
	}
}

void print_array(int* L, int size) {
	printf("array: ");
	for (int i = 0; i < size; ++i) {
		printf("%d ", L[i]);
	}
	printf("\n");
}

int main (int argc, char** argv) {
	int L[] = {18, 7, 5, 8, 99};
	int size = sizeof(L) / sizeof(int);
	insert_sort(L, size);
	print_array(L, size);
	return 0;
}
