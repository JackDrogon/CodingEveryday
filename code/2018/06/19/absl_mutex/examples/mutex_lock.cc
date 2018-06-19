#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <memory>

using namespace std;

#include "absl/synchronization/mutex.h"

void func(absl::Mutex &mutex_, int &count)
{
	for (int i = 0; i < 100000; ++i) {
		absl::MutexLock lock(&mutex_);
		++count;
	}
}

int main()
{
	absl::Mutex mutex_;
	int count = 0;
	vector<std::thread> threads;
	for (int i = 0; i < 10; ++i) {
		threads.emplace_back(func, std::ref(mutex_), std::ref(count));
	}
	for (auto &thread : threads) {
		thread.join();
	}

	cout << "count: " << count << endl;

	return 0;
}
