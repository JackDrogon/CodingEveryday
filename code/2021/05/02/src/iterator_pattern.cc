#include "iterator_pattern.h"

#include <memory>

bool BookShelfIterator::HasNext() const noexcept
{
	return current_index_ < bookself_->GetSize();
}

Book &BookShelfIterator::Next() noexcept
{
	return bookself_->GetBookAt(current_index_++);
}

std::unique_ptr<Iterator<Book>> BookShelf::NewIterator() noexcept
{
	return std::make_unique<BookShelfIterator>(this);
}
