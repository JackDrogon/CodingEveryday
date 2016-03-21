#ifndef __Mutex_H__
#define __Mutex_H__

// TODO: Add namespace or inline

/*
 * #if (__has_feature(cxx_noexcept))
 * #  define _NOEXCEPT noexcept
 * #  define _NOEXCEPT_(x) noexcept(x)
 * #  define _NOEXCEPT_OR_FALSE(x) noexcept(x)
 * #else
 * #  define _NOEXCEPT throw()
 * #  define _NOEXCEPT_(x)
 * #  define _NOEXCEPT_OR_FALSE(x) false
 * #endif
 *
 */

#include <pthread.h>

class Mutex
{
public:
	/* constexpr Mutex() noexcept : mutex_(PTHREAD_MUTEX_INITIALIZER) {} */

	Mutex() noexcept { mutex_ = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER; }
	~Mutex() { pthread_mutex_destroy(&mutex_); }

	void Lock() noexcept;

	bool TryLock();
	void UnLock() noexcept;

	typedef pthread_mutex_t *native_handle_type;
	native_handle_type native_handle() { return &mutex_; }

private:
	pthread_mutex_t mutex_;

	Mutex(const Mutex &);		 // = delete;
	Mutex &operator=(const Mutex &); // = delete;
};


void Mutex::UnLock() noexcept { pthread_mutex_unlock(&mutex_); }

bool Mutex::TryLock() { return pthread_mutex_trylock(&mutex_) == 0; }

template <typename _Mutex>
class LockGuard
{
public:
	typedef _Mutex mutex_type;
	LockGuard(mutex_type& mutex) : mutex_(mutex) { mutex_.Lock(); }
	~LockGuard() { mutex_.UnLock(); }
private:
	mutex_type& mutex_;

	LockGuard(const LockGuard&);	    // = delete;
	LockGuard& operator=(const LockGuard&); // = delete;
};

using MutexGuard = LockGuard<Mutex>;

#endif // __Mutex_H__
