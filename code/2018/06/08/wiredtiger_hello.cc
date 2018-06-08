#include <iostream>
#include <sys/stat.h>

#include <wiredtiger.h>

using namespace std;

#define error_check(call)                                                      \
	do {                                                                   \
		int __r;                                                       \
		if ((__r = (call)) != 0 && __r != ENOTSUP)                     \
			abort();                                               \
	} while (0)

const char *example_setup(int argc, char *argv[])
{
	const char *home;
	(void)argc; /* Unused variable */
	(void)argv;
	if ((home = getenv("WIREDTIGER_HOME")) == NULL) {
		home = "WT_HOME";
	}
	mkdir(home, 0755);

	return home;
}

int main(int argc, char *argv[])
{
	const char *home;

	WT_CONNECTION *conn;
	WT_SESSION *session;

	home = example_setup(argc, argv);

	/* Open a connection to the database, creating it if necessary. */
	error_check(wiredtiger_open(home, NULL, "create", &conn));

	/* Open a session for the current thread's work. */
	error_check(conn->open_session(conn, NULL, NULL, &session));

	/* Do some work... */

	/* Note: closing the connection implicitly closes open session(s). */
	error_check(conn->close(conn, NULL));

	return (EXIT_SUCCESS);
}
