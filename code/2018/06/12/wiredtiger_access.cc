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

// demonstrates how to create and access a simple table.
static void access_example(void)
{
	/*! [access example connection] */
	WT_CONNECTION *conn;
	WT_CURSOR *cursor;
	WT_SESSION *session;
	const char *key, *value;
	int ret;

	/* Open a connection to the database, creating it if necessary. */
	error_check(wiredtiger_open(home, NULL, "create", &conn));

	/* Open a session handle for the database. */
	error_check(conn->open_session(conn, NULL, NULL, &session));
	/*! [access example connection] */

	/*! [access example table create] */
	error_check(session->create(session, "table:access",
				    "key_format=S,value_format=S"));
	/*! [access example table create] */

	/*! [access example cursor open] */
	error_check(
	    session->open_cursor(session, "table:access", NULL, NULL, &cursor));
	/*! [access example cursor open] */

	/*! [access example cursor insert] */
	cursor->set_key(cursor, "hello"); /* Insert a record. */
	cursor->set_value(cursor, "world");
	error_check(cursor->insert(cursor));
	/*! [access example cursor insert] */

	/*! [access example cursor list] */
	error_check(cursor->reset(cursor)); /* Restart the scan. */
	while ((ret = cursor->next(cursor)) == 0) {
		error_check(cursor->get_key(cursor, &key));
		error_check(cursor->get_value(cursor, &value));

		printf("Got record: %s : %s\n", key, value);
	}
	assert(ret == WT_NOTFOUND); /* Check for end-of-table. */
	/*! [access example cursor list] */

	/*! [access example close] */
	error_check(conn->close(conn, NULL)); /* Close all handles. */
					      /*! [access example close] */
}

int main(int argc, char *argv[])
{
	home = example_setup(argc, argv);

	access_example();

	return (EXIT_SUCCESS);
}
