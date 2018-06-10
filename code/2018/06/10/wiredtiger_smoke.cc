#include <stdlib.h>

#include <wiredtiger.h>

/*
 *	A simple program you can build to prove include files and libraries
 * are linking correctly.
 */

int
main(int argc, char *argv[])
{
	WT_CONNECTION *conn;
	int ret;

	(void)argc;					/* Unused variable */

	/*
	 * This code deliberately doesn't use the standard test_util macros,
	 * we don't want to link against that code to smoke-test a build.
	 */
	if ((ret = system("rm -rf WT_HOME && mkdir WT_HOME")) != 0) {
		fprintf(stderr,
		    "Failed to clean up prior to running example.\n");
		return (EXIT_FAILURE);
	}

	/* Open a connection to the database, creating it if necessary. */
	if ((ret = wiredtiger_open("WT_HOME", NULL, "create", &conn)) != 0) {
		fprintf(stderr,
		    "%s: wiredtiger_open: %s\n",
		    argv[0], wiredtiger_strerror(ret));
		return (EXIT_FAILURE);
	}

	/* Close the connection to the database. */
	if ((ret = conn->close(conn, NULL)) != 0) {
		fprintf(stderr,
		    "%s: WT_CONNECTION.close: %s\n",
		    argv[0], wiredtiger_strerror(ret));
		return (EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}
