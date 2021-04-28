#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>


template <typename Object> class Iterator {
    public:
	Iterator() = default;
	virtual ~Iterator() = default;

	virtual bool HasNext() const = 0;
	virtual Object &Next() = 0;
};

template <typename Object> class Aggregate {
    public:
	Aggregate() = default;
	virtual ~Aggregate() = default;

	virtual std::unique_ptr<Iterator<Object>> NewIterator() = 0;
};

class Book {
    public:
	Book(std::string name) : name_(std::move(name))
	{
	}

	std::string Name() const
	{
		return name_;
	}

    private:
	std::string name_;
};

class BookShelf final : public Aggregate<Book> {
    public:
	BookShelf()
	{
	}

	auto GetSize() const
	{
		return books_.size();
	}

	// TODO: const
	[[nodiscard]] auto GetBookAt(size_t index) -> Book &
	{
		return books_[index];
	}

	[[nodiscard]] auto GetBookAt(size_t index) const -> const Book &
	{
		return books_[index];
	}

	void AppendBook(std::string name)
	{
		books_.emplace_back(std::move(name));
	}

	virtual std::unique_ptr<Iterator<Book>> NewIterator() override;

    private:
	std::vector<Book> books_;
};

class BookShelfIterator final : public Iterator<Book> {
    public:
	BookShelfIterator(BookShelf *bookself)
		: current_index_(0), bookself_(bookself)
	{
	}

	bool HasNext() const override;
	Book &Next() override;

    private:
	size_t current_index_;
	BookShelf *bookself_;
};
