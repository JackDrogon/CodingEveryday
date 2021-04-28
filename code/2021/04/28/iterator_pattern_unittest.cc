#include "iterator_pattern.h"

#include <vector>
#include <string>

#include <catch2/catch.hpp>

TEST_CASE("BookShelf Iterator iterate", "[iterator]")
{
	std::vector<std::string> v{ "Around the World in 80 Days", "Bible",
				    "Cinderella", "Daddy-Long-Legs" };
	BookShelf bookself;
	for (auto &&name : v) {
		bookself.AppendBook(name);
	}

	size_t idx = 0;
	auto iter = bookself.NewIterator();
	while (iter->HasNext()) {
		auto book = iter->Next();
		REQUIRE(book.Name() == v[idx++]);
	}
	REQUIRE(idx == v.size());
}
