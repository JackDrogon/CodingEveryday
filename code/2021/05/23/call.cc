#include <functional>
#include <iostream>
#include <memory>
#include <tuple>
#include <type_traits>
#include <utility>
using namespace std;


namespace
{
// using routine = void *(*)(void *);
using routine = void *(void *);

void *call(routine caller, void *arg)
{
	return caller(arg);
}

/// adapt to call

template <class Fp, class... Args, size_t... Indices>
inline void execute(std::tuple<Fp, Args...> &closure,
		    std::index_sequence<Indices...>)
{
	std::invoke(std::move(std::get<0>(closure)),
		    std::move(std::get<Indices + 1>(closure))...);
}

/// Fp = std::tuple<Functor, Args...>
template <class Fp> void *call_proxy(void *vp)
{
	std::unique_ptr<Fp> closure(static_cast<Fp *>(vp));
	using Index = std::make_index_sequence<
		std::tuple_size_v<std::remove_reference_t<Fp>> - 1>;

	execute(*closure, Index{});

	return nullptr;
}

template <class Type> inline typename decay<Type>::type decay_copy(Type &&t)
{
	return std::forward<Type>(t);
}

template <class Function, class... Args> void run(Function &&f, Args &&...args)
{
	using Gp = std::tuple<typename decay<Function>::type,
			      typename decay<Args>::type...>;
	auto p = std::make_unique<Gp>(decay_copy(std::forward<Function>(f)),
				      decay_copy(std::forward<Args>(args))...);
	call(&call_proxy<Gp>, p.get());

	(void)p.release();
}
} // namespace

int main()
{
	run([] { cout << "Hello, World!" << endl; });
}
