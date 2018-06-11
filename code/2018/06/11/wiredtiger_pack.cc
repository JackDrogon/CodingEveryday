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

static const char *home;

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

// This is an example demonstrating basic packing and unpacking of fields.

int main(int argc, char *argv[])
{
	WT_CONNECTION *conn;
	WT_SESSION *session;
	int i, j, k;

	home = example_setup(argc, argv);

	/* Open a connection to the database, creating it if necessary. */
	error_check(wiredtiger_open(home, NULL, "create", &conn));

	/* Open a session for the current thread's work. */
	error_check(conn->open_session(conn, NULL, NULL, &session));

	{
		/*! [packing] */
		size_t size;
		char buf[50];

		error_check(wiredtiger_struct_size(session, &size, "iii", 42,
						   1000, -9));
		if (size > sizeof(buf)) {
			/* Allocate a bigger buffer. */
		}

		error_check(wiredtiger_struct_pack(session, buf, size, "iii",
						   42, 1000, -9));

		error_check(wiredtiger_struct_unpack(session, buf, size, "iii",
						     &i, &j, &k));
		/*! [packing] */
	}

	/* Note: closing the connection implicitly closes open session(s). */
	error_check(conn->close(conn, NULL));

	return (EXIT_SUCCESS);
}
