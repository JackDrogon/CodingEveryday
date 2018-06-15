#include <iostream>
#include <thread>
#include <vector>
#include <sys/stat.h>

#include <wiredtiger.h>

using namespace std;

// XXX(DOC): This is an example demonstrating ways to extend WiredTiger with
// extractors, collators and loadable modules.

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
	if ((home = getenv("WIREDTIGER_HOME")) == nullptr) {
		home = "WT_HOME";
	}
	mkdir(home, 0755);

	return home;
}

/*! [case insensitive comparator] */
/* A simple case insensitive comparator. */
static int __compare_nocase(WT_COLLATOR *collator, WT_SESSION *session,
			    const WT_ITEM *v1, const WT_ITEM *v2, int *cmp)
{
	const char *s1 = (const char *)v1->data;
	const char *s2 = (const char *)v2->data;

	(void)session;  /* unused variable */
	(void)collator; /* unused variable */

	*cmp = strcasecmp(s1, s2);
	return (0);
}

static WT_COLLATOR nocasecoll = {__compare_nocase, NULL, NULL};
/*! [case insensitive comparator] */

/*! [n character comparator] */
/*
 * Comparator that only compares the first N prefix characters of the string.
 * This has associated data, so we need to extend WT_COLLATOR.
 */
typedef struct {
	WT_COLLATOR iface;
	uint32_t maxlen;
} PREFIX_COLLATOR;

static int __compare_prefixes(WT_COLLATOR *collator, WT_SESSION *session,
			      const WT_ITEM *v1, const WT_ITEM *v2, int *cmp)
{
	PREFIX_COLLATOR *pcoll = (PREFIX_COLLATOR *)collator;
	const char *s1 = (const char *)v1->data;
	const char *s2 = (const char *)v2->data;

	(void)session; /* unused */

	*cmp = strncmp(s1, s2, pcoll->maxlen);
	return (0);
}

static PREFIX_COLLATOR pcoll10 = {{__compare_prefixes, NULL, NULL}, 10};
/*! [n character comparator] */

int main(int argc, char *argv[])
{
	WT_CONNECTION *conn;
	WT_SESSION *session;

	home = example_setup(argc, argv);

	/* Open a connection to the database, creating it if necessary. */
	error_check(wiredtiger_open(home, NULL, "create", &conn));

	/*! [add collator nocase] */
	error_check(conn->add_collator(conn, "nocase", &nocasecoll, NULL));
	/*! [add collator nocase] */
	/*! [add collator prefix10] */
	error_check(conn->add_collator(conn, "prefix10", &pcoll10.iface, NULL));

	/* Open a session for the current thread's work. */
	error_check(conn->open_session(conn, NULL, NULL, &session));

	/* Do some work... */

	error_check(conn->close(conn, NULL));
	/*! [add collator prefix10] */

	return (EXIT_SUCCESS);
}
