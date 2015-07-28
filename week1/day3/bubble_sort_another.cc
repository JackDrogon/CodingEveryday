#include <iostream>
using namespace std;

void print_arr(int arr[], size_t n);
void bubble_sort(int arr[], const size_t n);

int main()
{
	int arr[15] = {1, 3, 6, 7, 8, 9, 10, 2, 5, 4, 14, 12, 13, 11};

	cout << "Before Bubble Sort, Array: ";
	print_arr(arr, 15);

	bubble_sort(arr, 15);

	cout << "After Bubble Sort, Array: ";
	print_arr(arr, 15);

	return 0;
}

void print_arr(int arr[], size_t n){
	for (size_t i = 0; i < n; ++i) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

void bubble_sort(int arr[], const size_t n)
{
	if (n <= 1) return;
	for (size_t i = 0; i < n-1; ++i) {
		// 此处是相邻交换较小的数在前，由于是从最后一个开始的，因而会依次得到最小，次小，复杂度恒为O(n^2), 比insert sort的常数系数大
		for (size_t j = n-1; j > i; --j) {
			if (arr[j] < arr[j-1]) {
				swap(arr[j], arr[j-1]);
			}
		}
	}
}
