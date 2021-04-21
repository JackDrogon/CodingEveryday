#include "boost/di.hpp"

namespace di = boost::di;

class Greater;

template <class T = Greater> struct example {
	using type = T;
};

struct hello {
};

int main()
{
	const auto injector =
		di::make_injector(di::bind<Greater>().to<hello>());

	auto object = injector.create<example>();
	static_assert(std::is_same<hello, decltype(object)::type>{}, "");
}
