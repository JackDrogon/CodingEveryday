#ifndef DROGON_COLLECTION_
#define DROGON_COLLECTION_

#include <utility>
#include <vector>

// TODO: Think about using class Collection or namespace Collection
// I like namespace Collection more

// TODO: Use boost processor, to use list -> idom

class Collection
{
public:
	template <typename T, typename F> static void foreach(T &coll, F fun);
	template <typename T, typename F> static T map(T &coll, F fun);
	template <typename T, typename F> static T filter(T &coll, F fun);
	template <typename T1, typename T2> static std::pair<T1, T2> zip(T1 &coll1, T2 &coll2);
};

template <typename T, typename F>
void Collection::foreach(T &coll, F fun)
{
	for (auto &ele : coll) {
		fun(ele);
	}
}

template <typename T, typename F>
static T map(T &coll, F fun)
{
	// need T have insert method
	// FIXME: use move, rvalue to return => coll_r
	T coll_r;
	for (auto &ele : coll) {
		coll_r.insert(fun(ele));
	}

	return coll_r;
}

template <typename T, typename F>
static T filter(T &coll, F fun)
{
	// need T have insert method
	// FIXME: use move, rvalue to return => coll_r
	T coll_r;
	for (auto iter = begin(coll); iter != end(coll); ++iter) {
		if (fun(*iter)) coll_r.insert(*iter);
	}

	return coll_r;
}

template <typename T1, typename T2> static std::vector<std::pair<T1, T2>>
zip(T1 &coll1, T2 &coll2)
{
	// TODO: coll1.size != coll2.size
	// use decltype...
	std::vector<std::pair<T1, T2>> coll_r;
	for (auto iter1 = begin(coll1), iter2 = begin(coll2); iter1 != end(coll1) && iter2 != end(coll2); ++iter1, ++iter2) {
		coll_r.push_back(make_pair(*iter1, *iter2));
	}
	return coll_r;
}

#endif
