#include <vector>

#include <fmt/ranges.h>

int main()
{
	std::vector<int> v = { 1, 2, 3, 4, 5 };
	fmt::print("{}\n", v);

	return 0;
}
