#pragma once

#include <cstddef>  // for size_t
#include <memory>   // for unique_ptr
#include <vector>   // for vector
#include <string>   // for string
#include <utility>  // for move

template <typename Object> class Iterator {
    public:
	Iterator() noexcept = default;
	virtual ~Iterator() noexcept = default;

	[[nodiscard]] virtual bool HasNext() const noexcept = 0;
	[[nodiscard]] virtual Object &Next() noexcept = 0;
};

template <typename Object> class Aggregate {
    public:
	Aggregate() noexcept = default;
	virtual ~Aggregate() noexcept = default;

	[[nodiscard]] virtual std::unique_ptr<Iterator<Object>> NewIterator() noexcept = 0;
};

class Book {
    public:
	explicit Book(std::string name) noexcept : name_(std::move(name))
	{
	}

	[[nodiscard]] std::string Name() const noexcept
	{
		return name_;
	}

    private:
	std::string name_;
};

class BookShelf final : public Aggregate<Book> {
    public:
	BookShelf() noexcept = default;

	[[nodiscard]] auto GetSize() const noexcept
	{
		return books_.size();
	}

	[[nodiscard]] auto GetBookAt(size_t index) noexcept -> Book &
	{
		return books_[index];
	}

	[[nodiscard]] auto GetBookAt(size_t index) const noexcept -> const Book &
	{
		return books_[index];
	}

	void AppendBook(std::string name)
	{
		books_.emplace_back(std::move(name));
	}

	[[nodiscard]] std::unique_ptr<Iterator<Book>> NewIterator() noexcept override;

    private:
	std::vector<Book> books_;
};

class BookShelfIterator final : public Iterator<Book> {
    public:
	BookShelfIterator(BookShelf *bookself) noexcept
		: current_index_(0), bookself_(bookself)
	{
	}

	bool HasNext() const noexcept override;
	Book &Next() noexcept override;

    private:
	size_t current_index_;
	BookShelf *bookself_;
};
