#include <pthread.h>

namespace drogon {
class Mutex {
public:
	Mutex()
	{
		pthread_mutex_init(&mu_, NULL);
	}

	~Mutex()
	{
		pthread_mutex_destroy(&mu_);
	}

	void Synchronize()
	{
		Lock();
		UnLock();
	}

	void Lock()
	{
		pthread_mutex_lock(&mu_);
	}

	void UnLock()
	{
		pthread_mutex_unlock(&mu_);
	}

	void Locked()
	{
	}

private:
	pthread_mutex_t mu_;
};
} // namespace drogon
