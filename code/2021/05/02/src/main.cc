#include <iostream>
using namespace std;

#include "iterator_pattern.h"

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
