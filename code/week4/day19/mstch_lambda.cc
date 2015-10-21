#include <iostream>
#include <mstch/mstch.hpp>

int main()
{

	std::string view{"Hello {{lambda}}!"};
	mstch::map context{{"lambda", mstch::lambda{[]() -> mstch::node {
				    return std::string{"World"};
			    }}}};

	std::cout << mstch::render(view, context) << std::endl;
	return 0;
}
