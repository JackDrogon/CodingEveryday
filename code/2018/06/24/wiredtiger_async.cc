#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <errno.h>

#include <sys/stat.h>

#include <wiredtiger.h>

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

static const char *home;
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

#if defined(_lint)
#define ATOMIC_ADD(v, val) ((v) += (val), (v))
#elif defined(_WIN32)
#define ATOMIC_ADD(v, val) (_InterlockedExchangeAdd(&(v), val) + val)
#else
#define ATOMIC_ADD(v, val) __sync_add_and_fetch(&(v), val)
#endif

static int global_error = 0;

/*! [async example callback implementation] */
typedef struct {
	WT_ASYNC_CALLBACK iface;
	uint32_t num_keys;
} ASYNC_KEYS;

static int async_callback(WT_ASYNC_CALLBACK *cb, WT_ASYNC_OP *op,
			  int wiredtiger_error, uint32_t flags)
{
	ASYNC_KEYS *asynckey = (ASYNC_KEYS *)cb;
	WT_ASYNC_OPTYPE type;
	WT_ITEM k, v;
	const char *key, *value;
	uint64_t id;

	(void)flags; /* Unused */

	/*! [async get type] */
	/* Retrieve the operation's WT_ASYNC_OPTYPE type. */
	type = op->get_type(op);
	/*! [async get type] */

	/*! [async get identifier] */
	/* Retrieve the operation's 64-bit identifier. */
	id = op->get_id(op);
	/*! [async get identifier] */

	/* Check for a WiredTiger error. */
	if (wiredtiger_error != 0) {
		fprintf(stderr, "ID %" PRIu64 " error %d: %s\n", id,
			wiredtiger_error,
			wiredtiger_strerror(wiredtiger_error));
		global_error = wiredtiger_error;
		return (1);
	}

	/* If doing a search, retrieve the key/value pair. */
	if (type == WT_AOP_SEARCH) {
		/*! [async get the operation's string key] */
		error_check(op->get_key(op, &k));
		key = static_cast<const char *>(k.data);
		/*! [async get the operation's string key] */
		/*! [async get the operation's string value] */
		error_check(op->get_value(op, &v));
		value = static_cast<const char *>(v.data);
		/*! [async get the operation's string value] */
		ATOMIC_ADD(asynckey->num_keys, 1);
		printf("Id %" PRIu64 " got record: %s : %s\n", id, key, value);
	}
	return (0);
}
/*! [async example callback implementation] */

static ASYNC_KEYS ex_asynckeys = {{async_callback}, 0};

#define MAX_KEYS 15

int main(int argc, char *argv[])
{
	WT_ASYNC_OP *op;
	WT_CONNECTION *conn;
	WT_SESSION *session;
	int i, ret;
	char k[MAX_KEYS][16], v[MAX_KEYS][16];

	home = example_setup(argc, argv);

	/*! [async example connection] */
	error_check(wiredtiger_open(home, NULL,
				    "create,cache_size=100MB,"
				    "async=(enabled=true,ops_max=20,threads=2)",
				    &conn));
	/*! [async example connection] */

	/*! [async example table create] */
	error_check(conn->open_session(conn, NULL, NULL, &session));
	error_check(session->create(session, "table:async",
				    "key_format=S,value_format=S"));
	/*! [async example table create] */

	/* Insert a set of keys asynchronously. */
	for (i = 0; i < MAX_KEYS; i++) {
		/*! [async handle allocation] */
		while ((ret = conn->async_new_op(conn, "table:async", NULL,
						 &ex_asynckeys.iface, &op)) !=
		       0) {
			/*
			 * If we used up all the handles, pause and retry to
			 * give the workers a chance to catch up.
			 */
			fprintf(
			    stderr,
			    "asynchronous operation handle not available\n");
			if (ret == EBUSY)
				sleep(1);
			else
				return (EXIT_FAILURE);
		}
		/*! [async handle allocation] */

		/*! [async insert] */
		/*
		 * Set the operation's string key and value, and then do
		 * an asynchronous insert.
		 */
		/*! [async set the operation's string key] */
		(void)snprintf(k[i], sizeof(k), "key%d", i);
		op->set_key(op, k[i]);
		/*! [async set the operation's string key] */

		/*! [async set the operation's string value] */
		(void)snprintf(v[i], sizeof(v), "value%d", i);
		op->set_value(op, v[i]);
		/*! [async set the operation's string value] */

		error_check(op->insert(op));
		/*! [async insert] */
	}

	/*! [async flush] */
	/* Wait for all outstanding operations to complete. */
	error_check(conn->async_flush(conn));
	/*! [async flush] */

	/*! [async compaction] */
	/*
	 * Compact a table asynchronously, limiting the run-time to 5 minutes.
	 */
	error_check(conn->async_new_op(conn, "table:async", "timeout=300",
				       &ex_asynckeys.iface, &op));
	error_check(op->compact(op));
	/*! [async compaction] */

	/* Search for the keys we just inserted, asynchronously. */
	for (i = 0; i < MAX_KEYS; i++) {
		while ((ret = conn->async_new_op(conn, "table:async", NULL,
						 &ex_asynckeys.iface, &op)) !=
		       0) {
			/*
			 * If we used up all the handles, pause and retry to
			 * give the workers a chance to catch up.
			 */
			fprintf(
			    stderr,
			    "asynchronous operation handle not available\n");
			if (ret == EBUSY)
				sleep(1);
			else
				return (EXIT_FAILURE);
		}

		/*! [async search] */
		/*
		 * Set the operation's string key and value, and then do
		 * an asynchronous search.
		 */
		(void)snprintf(k[i], sizeof(k), "key%d", i);
		op->set_key(op, k[i]);
		error_check(op->search(op));
		/*! [async search] */
	}

	/*
	 * Connection close automatically does an async_flush so it will wait
	 * for all queued search operations to complete.
	 */
	error_check(conn->close(conn, NULL));

	printf("Searched for %" PRIu32 " keys\n", ex_asynckeys.num_keys);

	return (EXIT_SUCCESS);
}
