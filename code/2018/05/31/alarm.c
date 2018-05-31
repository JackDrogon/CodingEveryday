#include <stdio.h>
#include <signal.h>
#include <unistd.h>

typedef void signal_handler(int);

static void sig_alrm(int signo) { puts("Receive alarm"); }

int main()
{
	signal(SIGALRM, sig_alrm);
	alarm(5);
	pause();

	return 0;
}
