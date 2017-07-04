#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/fcntl.h>

static void daemonize(char *pidfile) {
    int fd;
    FILE *fp;

    if (fork() != 0) exit(0); /* parent exits */
    printf("New pid: %d\n", getpid());
    setsid(); /* create a new session */

    /* Every output goes to /dev/null. If Redis is daemonized but
     * the 'logfile' is set to 'stdout' in the configuration file
     * it will not log at all. */
    if ((fd = open("/dev/null", O_RDWR, 0)) != -1) {
        dup2(fd, STDIN_FILENO);
        dup2(fd, STDOUT_FILENO);
        dup2(fd, STDERR_FILENO);
        if (fd > STDERR_FILENO) close(fd);
    }
    /* Try to write the pid file */
    fp = fopen(pidfile, "w");
    if (fp) {
        fprintf(fp,"%d\n",getpid());
        fclose(fp);
    }
}

int main(int argc, char *argv[])
{
	char pidfile[64];
	strncpy(pidfile, argv[0], 64);
	strncat(pidfile, ".pid", 64);

	daemonize(pidfile);
	sleep(15);

	return 0;
}
