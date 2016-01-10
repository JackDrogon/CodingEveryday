//============================================================
// server.cc which hosts on *:19870
//============================================================

#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	void *ctx = zmq_init(1);
	printf("bind to '*:19870'\n");
	void *rep = zmq_socket(ctx, ZMQ_REP);
	zmq_bind(rep, "tcp://*:19870");
	while (1) {
		zmq_msg_t request;
		zmq_msg_init(&request);
		// 0 means in block way
		zmq_recv(rep, &request, 0);
		const char *s = (const char *)zmq_msg_data(&request);
		printf("[S]recv '%s'\n", s);
		zmq_msg_t reply;
		// include trailing '\0'.
		zmq_msg_init_size(&reply, strlen(s) + 1);
		memcpy(zmq_msg_data(&reply), s, strlen(s) + 1);
		zmq_msg_close(&request);
		// 0 means in block way.
		printf("[S]send '%s'\n", s);
		zmq_send(rep, &reply, 0);
		zmq_msg_close(&reply);
	}
	zmq_close(rep);
	zmq_term(ctx);
	return 0;
}
