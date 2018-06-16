#include <iostream>
#include <thread>
#include <vector>
#include <sys/stat.h>

#include <wiredtiger.h>

using namespace std;

// XXX(DOC): Demonstrate how to use the WiredTiger event handler mechanism.

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

int handle_wiredtiger_error(WT_EVENT_HANDLER *, WT_SESSION *, int,
			    const char *);
int handle_wiredtiger_message(WT_EVENT_HANDLER *, WT_SESSION *, const char *);

/*! [Function event_handler] */
/*
 * Create our own event handler structure to allow us to pass context through
 * to event handler callbacks. For this to work the WiredTiger event handler
 * must appear first in our custom event handler structure.
 */
typedef struct {
	WT_EVENT_HANDLER h;
	const char *app_id;
} CUSTOM_EVENT_HANDLER;

/*
 * handle_wiredtiger_error --
 *	Function to handle error callbacks from WiredTiger.
 */
int handle_wiredtiger_error(WT_EVENT_HANDLER *handler, WT_SESSION *session,
			    int error, const char *message)
{
	CUSTOM_EVENT_HANDLER *custom_handler;

	/* Cast the handler back to our custom handler. */
	custom_handler = (CUSTOM_EVENT_HANDLER *)handler;

	/* Report the error on the console. */
	fprintf(stderr, "app_id %s, thread context %p, error %d, message %s\n",
		custom_handler->app_id, (void *)session, error, message);

	/* Exit if the database has a fatal error. */
	if (error == WT_PANIC)
		exit(1);

	return (0);
}

/*
 * handle_wiredtiger_message --
 *	Function to handle message callbacks from WiredTiger.
 */
int handle_wiredtiger_message(WT_EVENT_HANDLER *handler, WT_SESSION *session,
			      const char *message)
{
	/* Cast the handler back to our custom handler. */
	printf("app id %s, thread context %p, message %s\n",
	       ((CUSTOM_EVENT_HANDLER *)handler)->app_id, (void *)session,
	       message);

	return (0);
}
/*! [Function event_handler] */

static void config_event_handler(void)
{
	WT_CONNECTION *conn;
	WT_SESSION *session;

	/*! [Configure event_handler] */
	CUSTOM_EVENT_HANDLER event_handler;

	event_handler.h.handle_error = handle_wiredtiger_error;
	event_handler.h.handle_message = handle_wiredtiger_message;
	/* Set handlers to NULL to use the default handler. */
	event_handler.h.handle_progress = NULL;
	event_handler.h.handle_close = NULL;
	event_handler.app_id = "example_event_handler";

	error_check(wiredtiger_open(home, (WT_EVENT_HANDLER *)&event_handler,
				    "create", &conn));
	/*! [Configure event_handler] */

	/* Make an invalid API call, to ensure the event handler works. */
	fprintf(stderr,
		"ex_event_handler: expect an error message to follow:\n");
	(void)conn->open_session(conn, NULL, "isolation=invalid", &session);
	fprintf(stderr, "ex_event_handler: end of error message\n");

	error_check(conn->close(conn, NULL));
}

int main(int argc, char *argv[])
{
	home = example_setup(argc, argv);

	config_event_handler();

	return (EXIT_SUCCESS);
}
