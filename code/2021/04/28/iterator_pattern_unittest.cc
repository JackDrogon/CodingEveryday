#include "iterator_pattern.h"

#include <vector>
#include <string>

#include <catch2/catch.hpp>

TEST_CASE("GetSize", "[BookShelf]")
{
	{
		BookShelf bookself;
		REQUIRE(bookself.GetSize() == 0);

		bookself.AppendBook("hello");
		REQUIRE(bookself.GetSize() == 1);
	}

	{
		const BookShelf bookself;
		REQUIRE(bookself.GetSize() == 0);
	}
}

TEST_CASE("GetBookAt", "[BookShelf]")
{
	std::vector<std::string> v{ "Around the World in 80 Days", "Bible",
				    "Cinderella", "Daddy-Long-Legs" };
	BookShelf bookself;
	for (auto &&name : v) {
		bookself.AppendBook(name);
	}

	for (size_t idx = 0; idx < v.size(); ++idx) {
		REQUIRE(bookself.GetBookAt(idx).Name() == v[idx]);
	}
}

TEST_CASE("AppendBook", "[BookShelf]")
{
	std::vector<std::string> v{ "Around the World in 80 Days", "Bible",
				    "Cinderella", "Daddy-Long-Legs" };
	BookShelf bookself;
	for (auto &&name : v) {
		bookself.AppendBook(name);
	}

	REQUIRE(bookself.GetSize() == v.size());
}

TEST_CASE("Iterate", "[BookShelfIterator]")
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
