/*
 * Compile with:
 * cc -I/usr/local/include -o event-test event-test.c -L/usr/local/lib -levent
 */

#include "event_loop.h"

#include <functional>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/queue.h>
#include <sys/time.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

void fifo_read(int fd)
{
	char buf[255];
	int len;
	/* struct event *ev = arg; */

	/* Reschedule this event */
	/* event_add(ev, NULL); */
	/* fprintf(stderr, "Read From Event!\n"); */

	fprintf(stderr, "fifo_read called with fd: %d\n", fd);

	len = read(fd, buf, sizeof(buf) - 1);
	if (len == -1) {
		perror("read");
		return;
	} else if (len == 0) {
		fprintf(stderr, "Connection closed\n");
		return;
	}

	buf[len] = '\0';
	fprintf(stdout, "Read: %s", buf);
	fprintf(stderr, "End Event!\n");
}

int main(int argc, char **argv)
{
	struct stat st;
	char *fifo = "event.fifo";
	int socket;

	if (lstat(fifo, &st) == 0) {
		if ((st.st_mode & S_IFMT) == S_IFREG) {
			errno = EEXIST;
			perror("lstat");
			exit(1);
		}
	}

	unlink(fifo);
	if (mkfifo(fifo, 0600) == -1) {
		perror("mkfifo");
		exit(1);
	}

/* Linux pipes are broken, we need O_RDWR instead of O_RDONLY */
#ifdef __linux
	socket = open(fifo, O_RDWR | O_NONBLOCK, 0);
#else
	socket = open(fifo, O_RDONLY | O_NONBLOCK, 0);
#endif

	if (socket == -1) {
		perror("open");
		exit(1);
	}

	fprintf(stderr, "Write data to %s\n", fifo);

	
	Channel channel(socket);
	channel.SetReadCallback(std::bind(fifo_read, socket));
	EventLoop event_loop;

	event_loop.AddChannel(&channel);

	event_loop.Loop();

	return (0);
}
