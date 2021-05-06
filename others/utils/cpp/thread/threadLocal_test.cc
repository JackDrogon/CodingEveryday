#include "thread_local.h"

#include <string>
#include <stdio.h>
#include <thread>
#include <pthread.h>

using namespace std;

namespace
{
class Test
{
    public:
	Test()
	{
		printf("tid=%d, constructing %p\n", pthread_self(), this);
	}

	~Test()
	{
		printf("tid=%d, destructing %p %s\n", pthread_self(), this,
		       name_.c_str());
	}

	const string &name() const
	{
		return name_;
	}
	void setName(const string &n)
	{
		name_ = n;
	}

    private:
	string name_;
};
} // namespace

ThreadLocal<Test> testObj1;
ThreadLocal<Test> testObj2;

void print()
{
	printf("tid=%d, obj1 %p name=%s\n", pthread_self(), &testObj1.Value(),
	       testObj1.Value().name().c_str());
	printf("tid=%d, obj2 %p name=%s\n", pthread_self(), &testObj2.Value(),
	       testObj2.Value().name().c_str());
}

void threadFunc()
{
	print();
	testObj1.Value().setName("changed 1");
	testObj2.Value().setName("changed 42");
	print();
}

int main()
{
	testObj1.Value().setName("main one");
	print();
	thread t1(threadFunc);
	t1.join();

	testObj2.Value().setName("main two");
	print();

	pthread_exit(0);
}
