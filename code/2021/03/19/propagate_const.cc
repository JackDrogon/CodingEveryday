#include <iostream>
#include <memory>
#include <experimental/propagate_const>

class widget {
    public:
	widget(int);
	~widget(); // defined in the implementation file, where impl is a complete type
	// Note: calling draw() on moved-from object is UB
	widget(const widget &) = delete;
	widget(widget &&) = default;
	widget &operator=(const widget &) = delete;

	widget &operator=(widget &&) = default;

	// public API that will be forwarded to the implementation
	void draw() const;
	void draw();

	// public API that implementation has to call
	bool shown() const
	{
		return true;
	}

    private:
	class impl;
	std::experimental::propagate_const<std::unique_ptr<impl>> pImpl;
};

class widget::impl {
    public:
	void draw(const widget &w) const
	{
		// this call to public member function requires the back-reference
		if (w.shown()) {
			std::cout << "drawing a const widget " << n << '\n';
		}
	}
	void draw(const widget &w)
	{
		if (w.shown()) {
			std::cout << "drawing a non-const widget " << n << '\n';
		}
	}
	impl(int n) : n(n)
	{
	}

    private:
	int n; // private data
};

void widget::draw() const
{
	pImpl->draw(*this);
}

void widget::draw()
{
	pImpl->draw(*this);
}

widget::widget(int n) : pImpl{ std::make_unique<impl>(n) }
{
}

widget::~widget() = default;

int main()
{
	widget w(7);
	const widget w2(8);
	w.draw();
	w2.draw();
}
