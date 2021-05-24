#include <functional>  // for invoke
#include <iostream>    // for operator<<, endl, basic_ostream, cout, ostream
#include <memory>      // for make_unique, unique_ptr
#include <tuple>       // for get, tuple
#include <type_traits> // for decay, forward, move, remove_reference_t
#include <utility>     // for index_sequence, make_index_sequence


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
		    std::index_sequence<Indices...> /* index */)
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

template <class Type> inline typename std::decay_t<Type> decay_copy(Type &&t)
{
	return std::forward<Type>(t);
}

template <class Function, class... Args> void run(Function &&f, Args &&...args)
{
	using Gp = std::tuple<typename std::decay_t<Function>,
			      typename std::decay_t<Args>...>;
	auto p = std::make_unique<Gp>(decay_copy(std::forward<Function>(f)),
				      decay_copy(std::forward<Args>(args))...);
	call(&call_proxy<Gp>, p.get());

	(void)p.release();
}
} // namespace

int main()
{
	run([] { std::cout << "Hello, World!" << std::endl; });

	return 0;
}
