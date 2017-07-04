#include <iostream>
#include <cstring>
#include <cstdlib>
#include <pthread.h>
using namespace std;

static void *thread_func(void *arg)
{
	char *s = static_cast<char *>(arg);
	return reinterpret_cast<void *>(strlen(s));
}

int main()
{
	pthread_t t1;
	void *res;

	int s = pthread_create(&t1, NULL, thread_func, static_cast<void *>(const_cast<char *>("Hello world\n")));
	if (s != 0) {
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	puts("Message from main()");

	s = pthread_join(t1, &res);
	if (s != 0) {
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	cout << "Thread returned " << reinterpret_cast<long>(res) << endl;

	return 0;
}
