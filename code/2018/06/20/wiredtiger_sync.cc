#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <errno.h>
#include <sys/stat.h>

#include <wiredtiger.h>

// XXX(DOC): demonstrates how to use the transaction sync configuration.

static const char *const uri = "table:test";

#define CONN_CONFIG "create,cache_size=100MB,log=(archive=false,enabled=true)"
#define MAX_KEYS 100

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
	if ((home = getenv("WIREDTIGER_HOME")) == nullptr) {
		home = "WT_HOME";
	}
	mkdir(home, 0755);

	return home;
}

int main(int argc, char *argv[])
{
	WT_CONNECTION *wt_conn;
	WT_CURSOR *cursor;
	WT_SESSION *session;
	int i, record_count, ret;
	char k[32], v[32];
	const char *conf;

	const char *home;
	home = example_setup(argc, argv);
	error_check(wiredtiger_open(home, NULL, CONN_CONFIG, &wt_conn));

	error_check(wt_conn->open_session(wt_conn, NULL, NULL, &session));
	error_check(
	    session->create(session, uri, "key_format=S,value_format=S"));

	error_check(session->open_cursor(session, uri, NULL, NULL, &cursor));
	/*
	 * Perform some operations with individual auto-commit transactions.
	 */
	error_check(session->begin_transaction(session, NULL));
	for (record_count = 0, i = 0; i < MAX_KEYS; i++, record_count++) {
		if (i == MAX_KEYS / 2) {
			error_check(session->commit_transaction(
			    session, "sync=background"));
			ret =
			    session->transaction_sync(session, "timeout_ms=0");
			if (ret == ETIMEDOUT)
				printf("Transactions not yet stable\n");
			else if (ret != 0) {
				fprintf(stderr,
					"session.transaction_sync: error %s\n",
					session->strerror(session, ret));
				exit(1);
			}
			error_check(session->begin_transaction(session, NULL));
		} else {
			if ((record_count % 3) == 0)
				conf = "sync=background";
			else
				conf = "sync=off";
			error_check(session->commit_transaction(session, conf));
			error_check(session->begin_transaction(session, NULL));
		}
		(void)snprintf(k, sizeof(k), "key%d", i);
		(void)snprintf(v, sizeof(v), "value%d", i);
		cursor->set_key(cursor, k);
		cursor->set_value(cursor, v);
		error_check(cursor->insert(cursor));
	}
	error_check(session->commit_transaction(session, "sync=background"));
	printf("Wait forever until stable\n");
	error_check(session->transaction_sync(session, NULL));
	printf("Transactions now stable\n");
	error_check(session->begin_transaction(session, NULL));
	/*
	 * Perform some operations within a single transaction.
	 */
	for (i = MAX_KEYS; i < MAX_KEYS + 5; i++, record_count++) {
		(void)snprintf(k, sizeof(k), "key%d", i);
		(void)snprintf(v, sizeof(v), "value%d", i);
		cursor->set_key(cursor, k);
		cursor->set_value(cursor, v);
		error_check(cursor->insert(cursor));
	}
	error_check(session->commit_transaction(session, "sync=on"));
	error_check(session->transaction_sync(session, "timeout_ms=0"));

	/*
	 * Demonstrate using log_flush to force the log to disk.
	 */
	for (i = 0; i < MAX_KEYS; i++, record_count++) {
		(void)snprintf(k, sizeof(k), "key%d", record_count);
		(void)snprintf(v, sizeof(v), "value%d", record_count);
		cursor->set_key(cursor, k);
		cursor->set_value(cursor, v);
		error_check(cursor->insert(cursor));
	}
	error_check(session->log_flush(session, "sync=on"));

	for (i = 0; i < MAX_KEYS; i++, record_count++) {
		(void)snprintf(k, sizeof(k), "key%d", record_count);
		(void)snprintf(v, sizeof(v), "value%d", record_count);
		cursor->set_key(cursor, k);
		cursor->set_value(cursor, v);
		error_check(cursor->insert(cursor));
	}
	error_check(cursor->close(cursor));
	error_check(session->log_flush(session, "sync=off"));
	error_check(session->log_flush(session, "sync=on"));

	error_check(wt_conn->close(wt_conn, NULL));

	return (EXIT_SUCCESS);
}
