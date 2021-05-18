#include <iostream>            // for endl, basic_ostream, cout, ostream, std
#include <memory>              // for allocator, unique_ptr
#include <string>              // for operator<<

using namespace std;

#include "iterator_pattern.h"  // for BookShelf, Iterator, Book

int main()
{
	BookShelf bookself;
	bookself.AppendBook("Around the World in 80 Days");
	bookself.AppendBook("Bible");
	bookself.AppendBook("Cinderella");
	bookself.AppendBook("Daddy-Long-Legs");

	auto iter = bookself.NewIterator();
	while (iter->HasNext()) {
		auto book = iter->Next();
		std::cout << book.Name() << std::endl;
	}

	return 0;
}
