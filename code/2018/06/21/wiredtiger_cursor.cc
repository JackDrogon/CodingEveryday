#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <errno.h>
#include <sys/stat.h>

#include <wiredtiger.h>

// XXX(DOC): This is an example demonstrating some cursor types and operations.

void testutil_die(int e, const char *fmt, ...);

#define testutil_assert(a)                                                     \
	do {                                                                   \
		if (!(a))                                                      \
			testutil_die(0, "%s/%d: %s", __func__, __LINE__, #a);  \
	} while (0)

#define error_check(call)                                                      \
	do {                                                                   \
		int __r;                                                       \
		if ((__r = (call)) != 0 && __r != ENOTSUP)                     \
			testutil_die(__r, "%s/%d: %s", __func__, __LINE__,     \
				     #call);                                   \
	} while (0)

#define scan_end_check(a) testutil_assert(a)

static const char *progname = "program name not set";
const char *example_setup(int argc, char *argv[])
{
	const char *home;
	(void)argc; /* Unused variable */
	progname = argv[0];

	if ((home = getenv("WIREDTIGER_HOME")) == nullptr) {
		home = "WT_HOME";
	}
	mkdir(home, 0755);

	return home;
}

void testutil_die(int e, const char *fmt, ...)
{
	va_list ap;

	/* Flush output to be sure it doesn't mix with fatal errors. */
	(void)fflush(stdout);
	(void)fflush(stderr);


	fprintf(stderr, "%s: FAILED", progname);
	if (fmt != nullptr) {
		fprintf(stderr, ": ");
		va_start(ap, fmt);
		vfprintf(stderr, fmt, ap);
		va_end(ap);
	}
	if (e != 0)
		fprintf(stderr, ": %s", wiredtiger_strerror(e));
	fprintf(stderr, "\n");
	fprintf(stderr, "process aborting\n");

	abort();
}

int cursor_reset(WT_CURSOR *cursor);
int cursor_forward_scan(WT_CURSOR *cursor);
int cursor_reverse_scan(WT_CURSOR *cursor);
int cursor_search(WT_CURSOR *cursor);
int cursor_search_near(WT_CURSOR *cursor);
int cursor_insert(WT_CURSOR *cursor);
int cursor_update(WT_CURSOR *cursor);
int cursor_remove(WT_CURSOR *cursor);

static const char *home;

/*! [cursor next] */
int cursor_forward_scan(WT_CURSOR *cursor)
{
	const char *key, *value;
	int ret;

	while ((ret = cursor->next(cursor)) == 0) {
		error_check(cursor->get_key(cursor, &key));
		error_check(cursor->get_value(cursor, &value));
	}
	scan_end_check(ret == WT_NOTFOUND);

	return (0);
}
/*! [cursor next] */

/*! [cursor prev] */
int cursor_reverse_scan(WT_CURSOR *cursor)
{
	const char *key, *value;
	int ret;

	while ((ret = cursor->prev(cursor)) == 0) {
		error_check(cursor->get_key(cursor, &key));
		error_check(cursor->get_value(cursor, &value));
	}
	scan_end_check(ret == WT_NOTFOUND);

	return (0);
}
/*! [cursor prev] */

/*! [cursor reset] */
int cursor_reset(WT_CURSOR *cursor) { return (cursor->reset(cursor)); }
/*! [cursor reset] */

/*! [cursor search] */
int cursor_search(WT_CURSOR *cursor)
{
	const char *value;

	cursor->set_key(cursor, "foo");

	error_check(cursor->search(cursor));
	error_check(cursor->get_value(cursor, &value));

	return (0);
}
/*! [cursor search] */

/*! [cursor search near] */
int cursor_search_near(WT_CURSOR *cursor)
{
	const char *key, *value;
	int exact;

	cursor->set_key(cursor, "foo");

	error_check(cursor->search_near(cursor, &exact));
	switch (exact) {
	case -1: /* Returned key smaller than search key */
		error_check(cursor->get_key(cursor, &key));
		break;
	case 0: /* Exact match found */
		break;
	case 1: /* Returned key larger than search key */
		error_check(cursor->get_key(cursor, &key));
		break;
	}
	error_check(cursor->get_value(cursor, &value));

	return (0);
}
/*! [cursor search near] */

/*! [cursor insert] */
int cursor_insert(WT_CURSOR *cursor)
{
	cursor->set_key(cursor, "foo");
	cursor->set_value(cursor, "bar");

	return (cursor->insert(cursor));
}
/*! [cursor insert] */

/*! [cursor update] */
int cursor_update(WT_CURSOR *cursor)
{
	cursor->set_key(cursor, "foo");
	cursor->set_value(cursor, "newbar");

	return (cursor->update(cursor));
}
/*! [cursor update] */

/*! [cursor remove] */
int cursor_remove(WT_CURSOR *cursor)
{
	cursor->set_key(cursor, "foo");
	return (cursor->remove(cursor));
}
/*! [cursor remove] */

int main(int argc, char *argv[])
{
	WT_CONNECTION *conn;
	WT_CURSOR *cursor;
	WT_SESSION *session;

	home = example_setup(argc, argv);

	/* Open a connection to the database, creating it if necessary. */
	error_check(
	    wiredtiger_open(home, NULL, "create,statistics=(fast)", &conn));

	/* Open a session for the current thread's work. */
	error_check(conn->open_session(conn, NULL, NULL, &session));

	error_check(session->create(session, "table:world",
				    "key_format=r,value_format=5sii,"
				    "columns=(id,country,population,area)"));

	/*! [open cursor #1] */
	error_check(
	    session->open_cursor(session, "table:world", NULL, NULL, &cursor));
	/*! [open cursor #1] */

	/*! [open cursor #2] */
	error_check(session->open_cursor(
	    session, "table:world(country,population)", NULL, NULL, &cursor));
	/*! [open cursor #2] */

	/*! [open cursor #3] */
	error_check(
	    session->open_cursor(session, "statistics:", NULL, NULL, &cursor));
	/*! [open cursor #3] */

	/* Create a simple string table to illustrate basic operations. */
	error_check(session->create(session, "table:map",
				    "key_format=S,value_format=S"));
	error_check(
	    session->open_cursor(session, "table:map", NULL, NULL, &cursor));
	error_check(cursor_insert(cursor));
	error_check(cursor_reset(cursor));
	error_check(cursor_forward_scan(cursor));
	error_check(cursor_reset(cursor));
	error_check(cursor_reverse_scan(cursor));
	error_check(cursor_search_near(cursor));
	error_check(cursor_update(cursor));
	error_check(cursor_remove(cursor));
	error_check(cursor->close(cursor));

	/* Note: closing the connection implicitly closes open session(s). */
	error_check(conn->close(conn, NULL));

	return (EXIT_SUCCESS);
}
