#include <iostream>
#include <thread>
#include <vector>
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
	if ((home = getenv("WIREDTIGER_HOME")) == nullptr) {
		home = "WT_HOME";
	}
	mkdir(home, 0755);

	return home;
}

#define NUM_THREADS 10
/*! [thread scan] */
void *scan_thread(WT_CONNECTION *conn)
{
	WT_CURSOR *cursor;
	WT_SESSION *session;
	int ret;
	const char *key, *value;

	error_check(conn->open_session(conn, nullptr, nullptr, &session));
	error_check(session->open_cursor(session, "table:access", nullptr,
					 nullptr, &cursor));

	/* Show all records. */
	while ((ret = cursor->next(cursor)) == 0) {
		error_check(cursor->get_key(cursor, &key));
		error_check(cursor->get_value(cursor, &value));

		printf("Got record: %s : %s\n", key, value);
	}
	if (ret != WT_NOTFOUND)
		fprintf(stderr, "WT_CURSOR.next: %s\n",
			session->strerror(session, ret));

	return nullptr;
}
/*! [thread scan] */

/*! [thread main] */
int main(int argc, char *argv[])
{
	WT_CONNECTION *conn;
	WT_SESSION *session;
	WT_CURSOR *cursor;
	vector<std::thread> threads;

	int i;

	home = example_setup(argc, argv);

	error_check(wiredtiger_open(home, nullptr, "create", &conn));

	error_check(conn->open_session(conn, nullptr, nullptr, &session));
	error_check(session->create(session, "table:access",
				    "key_format=S,value_format=S"));
	error_check(session->open_cursor(session, "table:access", nullptr,
					 "overwrite", &cursor));
	cursor->set_key(cursor, "key1");
	cursor->set_value(cursor, "value1");
	error_check(cursor->insert(cursor));
	error_check(session->close(session, nullptr));

	for (i = 0; i < NUM_THREADS; i++) {
		threads.emplace_back(scan_thread, conn);
	}

	for (i = 0; i < NUM_THREADS; i++) {
		threads.at(i).join();
	}

	error_check(conn->close(conn, nullptr));

	return (EXIT_SUCCESS);
}
/*! [thread main] */
