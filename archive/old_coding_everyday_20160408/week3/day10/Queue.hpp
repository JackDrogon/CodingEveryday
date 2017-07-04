/* ************************************************************
 *  Queue.hpp
 *   - safer and more convenient queue class
 * ************************************************************/
#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <deque>
#include <exception>

template <typename T> class Queue
{
      protected:
	std::deque<T> c; // container for the elements

      public:
	// exception class for pop() and front() with empty queue
	class ReadEmptyQueue : public std::exception
	{
	      public:
		virtual const char *what() const throw()
		{
			return "read empty queue";
		}
	};

	// number of elements
	typename std::deque<T>::size_type size() const { return c.size(); }

	// is queue empty?
	bool empty() const { return c.empty(); }

	// insert element into the queue
	void push(const T &elem) { c.push_back(elem); }

	// remove next element from the queue and return its value
	T pop()
	{
		if (c.empty()) {
			throw ReadEmptyQueue();
		}
		T elem(c.front());
		c.pop_front();
		return elem;
	}

	// return value of next element
	T &front()
	{
		if (c.empty()) {
			throw ReadEmptyQueue();
		}
		return c.front();
	}
};

#endif /* QUEUE_HPP */
