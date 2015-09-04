#include <iostream>
using namespace std;

void print_arr(int arr[], size_t n);
void quick_sort(int arr[], const size_t left, const size_t right);

int main()
{
	int arr[15] = {1, 3, 6, 7, 8, 9, 10, 2, 5, 4, 14, 12, 13, 11};

	cout << "Before Quick Sort, Array: ";
	print_arr(arr, 15);

	quick_sort(arr, 0, 14);

	cout << "After Quick Sort, Array: ";
	print_arr(arr, 15);

	return 0;
}

void print_arr(int arr[], size_t n){
	for (size_t i = 0; i < n; ++i) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

void quick_sort(int arr[], const size_t left, const size_t right)
{
	if (left >= right) return;

	size_t last;
	swap(arr[left], arr[(left+right) >> 1]);
	last = left;
	for (auto i = left+1; i <= right; ++i) {
		if (arr[i] < arr[left]) swap(arr[++last], arr[i]);
	}
	swap(arr[left], arr[last]);
	quick_sort(arr, left, last); // 此处last-1有问题，容易弄成负数，如果是int还好，但是是size_t, 确实是有了问题。因此改为了last
	quick_sort(arr, last+1, right);
}
