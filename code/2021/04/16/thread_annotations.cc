#include "thread_annotations.h"

#include <mutex>
using namespace std;

class BankAccount {
    private:
	mutex mu;
	int balance GUARDED_BY(mu);

	void depositImpl(int amount)
	{
		balance +=
			amount; // WARNING! Cannot write balance without locking mu.
	}

	void withdrawImpl(int amount) REQUIRES(mu)
	{
		balance -= amount; // OK. Caller must have locked mu.
	}

    public:
	void withdraw(int amount)
	{
		mu.lock();
		withdrawImpl(amount); // OK.  We've locked mu.
	} // WARNING!  Failed to unlock mu.

	void transferFrom(BankAccount &b, int amount)
	{
		mu.lock();
		b.withdrawImpl(
			amount); // WARNING!  Calling withdrawImpl() requires locking b.mu.
		depositImpl(amount); // OK.  depositImpl() has no requirements.
		mu.unlock();
	}
};
