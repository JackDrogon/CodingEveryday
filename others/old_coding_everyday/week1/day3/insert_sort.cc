#include <iostream>
using namespace std;

void print_arr(int arr[], size_t n);
void insert_sort(int arr[], const size_t n);

int main()
{
	int arr[15] = {1, 3, 6, 7, 8, 9, 10, 2, 5, 4, 14, 12, 13, 11};

	cout << "Before Insert Sort, Array: ";
	print_arr(arr, 15);

	insert_sort(arr, 15);

	cout << "After Insert Sort, Array: ";
	print_arr(arr, 15);

	return 0;
}

void print_arr(int arr[], size_t n){
	for (size_t i = 0; i < n; ++i) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

void insert_sort(int arr[], const size_t n)
{
	if (n <= 1) return;
	for (size_t i = 1; i < n; ++i) {
		for (size_t j = i; j > 0; --j) {
			if (arr[j] < arr[j-1]) {
				swap(arr[j], arr[j-1]);
			} else {
				break;
			}
		}
	}
}
