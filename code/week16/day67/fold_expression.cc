#include <iostream>
#include <vector>

template <typename... Args> void printer(Args &&... args)
{
	(std::cout << ... << args) << '\n';
}

template <typename T, typename... Args>
void push_back_vec(std::vector<T> &v, Args &&... args)
{
	(v.push_back(args), ...);
}

int main()
{
	printer(1, 2, 3, "abc");

	std::vector<int> v;
	push_back_vec(v, 6, 2, 45, 12);
	push_back_vec(v, 1, 2, 9);

	for (int i : v) {
		std::cout << i << ' ';
	}
}
