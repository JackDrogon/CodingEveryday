#include <mstch/mstch.hpp>
#include <cassert>
#include <string>

int main()
{
	std::string view("Hello, world");
	mstch::map context;

	assert(mstch::render(view, context) == "Hello, world");
}
