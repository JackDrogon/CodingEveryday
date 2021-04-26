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
	[[nodiscard]] auto &GetBookAt(size_t index)
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

	bool HasNext() const override
	{
		return current_index_ < bookself_->GetSize();
	}

	Book &Next() override
	{
		return bookself_->GetBookAt(current_index_++);
	}

    private:
	size_t current_index_;
	BookShelf *bookself_;
};

std::unique_ptr<Iterator<Book>> BookShelf::NewIterator()
{
	return std::make_unique<BookShelfIterator>(this);
}

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
