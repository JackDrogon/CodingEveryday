#ifndef BLOCKING_QUEUE_H_
#define BLOCKING_QUEUE_H_

#include <deque>
#include <mutex>
#include <condition_variable>

template <typename T>
class BlockingQueue {
public:
	BlockingQueue() : queue_(), mutex_(), not_empty_(mutex_) {}

	void Put(const T& item)
	{
		std::lock_guard<std::mutex> lock(mutex_);
		queue_.push_back(item);
		not_empty_.notify_one();
	}

	void Put(const T&& item)
	{
		std::lock_guard<std::mutex> lock(mutex_);
		queue_.push_back(std::move(item));
		not_empty_.notify_one();
	}

	T Take()
	{
		std::lock_guard<std::mutex> lock(mutex_);
		// always use a while-loop, due to spurious wakeup
		while (queue_.empty()) { not_empty_.wait(); }
		assert(!queue_.empty());

		T front(std::move(queue_.front()));
		queue_.pop_front();

		return front;
	}

	size_t size() const
	{
		std::lock_guard<std::mutex> lock(mutex_);
		return queue_.size();
	}

private:
	std::deque<T> queue_;
	std::mutex mutex_;
	std::condition_variable not_empty_;
};

#endif // BLOCKING_QUEUE_H_
