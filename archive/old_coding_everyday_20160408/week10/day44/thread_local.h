#ifndef __THREAD_LOCAL_H__
#define __THREAD_LOCAL_H__

#include <cassert>
#include <sys/cdefs.h>
#include <pthread.h>

#define __THROW throw()

#ifdef CHECK_PTHREAD_RETURN_VALUE

#ifdef NDEBUG
__BEGIN_DECLS
extern void __assert_perror_fail(int errnum, const char *file,
				 unsigned int line,
				 const char *function) __THROW
    __attribute__((__noreturn__));
__END_DECLS
#endif

#define MCHECK(ret)                                                            \
	({                                                                     \
		__typeof__(ret) errnum = (ret);                                \
		if (__builtin_expect(errnum != 0, 0))                          \
			__assert_perror_fail(errnum, __FILE__, __LINE__,       \
					     __func__);                        \
	})

#else // CHECK_PTHREAD_RETURN_VALUE

#define MCHECK(ret)                                                            \
	({                                                                     \
		__typeof__(ret) errnum = (ret);                                \
		assert(errnum == 0);                                           \
		(void) errnum;                                                 \
	})

#endif // CHECK_PTHREAD_RETURN_VALUE

template <typename T> class ThreadLocal
{
      public:
	ThreadLocal()
	{
		MCHECK(pthread_key_create(&pkey_, &ThreadLocal::destructor));
	}

	~ThreadLocal() { MCHECK(pthread_key_delete(pkey_)); }

	T &value()
	{
		T *perThreadValue =
		    static_cast<T *>(pthread_getspecific(pkey_));
		if (!perThreadValue) {
			T *newObj = new T();
			MCHECK(pthread_setspecific(pkey_, newObj));
			perThreadValue = newObj;
		}
		return *perThreadValue;
	}

      private:
	static void destructor(void *x)
	{
		T *obj = static_cast<T *>(x);
		typedef char T_must_be_complete_type[sizeof(T) == 0 ? -1 : 1];
		T_must_be_complete_type dummy;
		(void)dummy;
		delete obj;
	}

      private:
	pthread_key_t pkey_;

	ThreadLocal(const ThreadLocal &);	    // = delete
	ThreadLocal &operator=(const ThreadLocal &); // = delete
};

#endif // __THREAD_LOCAL_H__
