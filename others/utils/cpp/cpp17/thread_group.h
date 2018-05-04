#pragma once

#include <list>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <memory>

// TODO: not completed

class thread_group
{
private:
	thread_group(const thread_group &) = delete;
	thread_group &operator=(const thread_group &) = delete;

public:
	thread_group() {};
	~thread_group()
	{
		for (auto &thread : threads_) delete thread;
	}

	template <typename _Fp, class ..._Args> std::thread *create_thread(_Fp &&__f, _Args &&...__args)
	{
		std::lock_guard<std::shared_mutex> guard(mutex_);
		std::unique_ptr<std::thread> new_thread(new std::thread(__f, __args));
		threads_.push_back(new_thread.get());
		return new_thread.release();
	}

	void add_thread(std::thread *thrd);
	void remove_thread(std::thread *thrd);
	bool is_this_thread_in();
	bool is_thread_in(std::thread *thrd);
	void join_all()
	{
		std::lock_guard<std::shared_mutex> guard(mutex_);
		for (auto &thread : threads_) {
			if (thread->joinable()) thread->join();
		}
	}

	// void interrupt_all();

	int size() const
	{
		std::lock_guard<std::shared_mutex> guard(mutex_);
		return threads_.size();
	}

private:
	std::list<std::thread*> threads_;
	mutable std::shared_mutex mutex_;
};
