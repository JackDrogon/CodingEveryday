#include "iterator_pattern.h"

bool BookShelfIterator::HasNext() const
{
	return current_index_ < bookself_->GetSize();
}

Book &BookShelfIterator::Next()
{
	return bookself_->GetBookAt(current_index_++);
}

std::unique_ptr<Iterator<Book>> BookShelf::NewIterator()
{
	return std::make_unique<BookShelfIterator>(this);
}
