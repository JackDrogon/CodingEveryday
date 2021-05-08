#include "iterator_pattern.h"

#include <string>
#include <vector>

#include <catch2/catch.hpp>

struct BookShelfCreator {
	BookShelfCreator()
		: booknames{ "Around the World in 80 Days", "Bible",
			     "Cinderella", "Daddy-Long-Legs" }
	{
		for (auto &&name : booknames) {
			bookshelf.AppendBook(name);
		}
	}

	std::vector<std::string> booknames;
	BookShelf bookshelf;
};

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
	BookShelfCreator bookshelf_creator;
	const auto &[booknames, bookshelf] = bookshelf_creator;

	for (size_t idx = 0; idx < booknames.size(); ++idx) {
		REQUIRE(bookshelf.GetBookAt(idx).Name() == booknames[idx]);
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

TEST_CASE("NewIterator", "[BookShelf]")
{
	BookShelfCreator bookshelf_creator;
	auto &[booknames, bookshelf] = bookshelf_creator;

	auto iter = bookshelf.NewIterator();
	REQUIRE(iter);

	auto &firstbook = iter->Next();
	REQUIRE(firstbook.Name() == booknames[0]);
}

TEST_CASE("Iterate", "[BookShelfIterator]")
{
	BookShelfCreator bookshelf_creator;
	auto &[booknames, bookshelf] = bookshelf_creator;

	size_t idx = 0;
	auto iter = bookshelf.NewIterator();
	while (iter->HasNext()) {
		auto book = iter->Next();
		REQUIRE(book.Name() == booknames[idx++]);
	}
	REQUIRE(idx == booknames.size());
}
