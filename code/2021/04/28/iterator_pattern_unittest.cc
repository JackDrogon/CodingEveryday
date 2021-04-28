#include "iterator_pattern.h"

#include <vector>
#include <string>

#include <catch2/catch.hpp>

TEST_CASE("GetSize", "[BookShelf]")
{
	SECTION("mutable bookshelf")
	{
		BookShelf bookshelf;
		REQUIRE(bookshelf.GetSize() == 0);

		bookshelf.AppendBook("hello");
		REQUIRE(bookshelf.GetSize() == 1);
	}

	SECTION("const bookshelf")
	{
		const BookShelf bookshelf;
		REQUIRE(bookshelf.GetSize() == 0);
	}
}

TEST_CASE("GetBookAt", "[BookShelf]")
{
	std::vector<std::string> v{ "Around the World in 80 Days", "Bible",
				    "Cinderella", "Daddy-Long-Legs" };
	BookShelf bookshelf;
	for (auto &&name : v) {
		bookshelf.AppendBook(name);
	}

	for (size_t idx = 0; idx < v.size(); ++idx) {
		REQUIRE(bookshelf.GetBookAt(idx).Name() == v[idx]);
	}
}

TEST_CASE("AppendBook", "[BookShelf]")
{
	std::vector<std::string> v{ "Around the World in 80 Days", "Bible",
				    "Cinderella", "Daddy-Long-Legs" };
	BookShelf bookshelf;
	for (auto &&name : v) {
		bookshelf.AppendBook(name);
	}

	REQUIRE(bookshelf.GetSize() == v.size());
}

TEST_CASE("Iterate", "[BookShelfIterator]")
{
	std::vector<std::string> v{ "Around the World in 80 Days", "Bible",
				    "Cinderella", "Daddy-Long-Legs" };
	BookShelf bookshelf;
	for (auto &&name : v) {
		bookshelf.AppendBook(name);
	}

	size_t idx = 0;
	auto iter = bookshelf.NewIterator();
	while (iter->HasNext()) {
		auto book = iter->Next();
		REQUIRE(book.Name() == v[idx++]);
	}
	REQUIRE(idx == v.size());
}
