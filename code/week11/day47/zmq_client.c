#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	void *ctx = zmq_init(1);
	printf("connect to server 'localhost:19870'\n");
	void *req = zmq_socket(ctx, ZMQ_REQ);
	zmq_connect(req, "tcp://localhost:19870");
	for (int i = 0; i < 10; i++) {
		zmq_msg_t request;
		zmq_msg_init_size(&request, 6);
		// including trailing '\0'.
		memcpy(zmq_msg_data(&request), "hello", 6);
		printf("[C]send 'hello'\n");
		// 0 means in block way.
		zmq_send(req, &request, 0);
		zmq_msg_close(&request);
		zmq_msg_t reply;
		zmq_msg_init(&reply);
		// 0 means in block way.
		zmq_recv(req, &reply, 0);
		printf("[C]recv '%s'\n", zmq_msg_data(&reply));
		zmq_msg_close(&reply);
	}
	zmq_close(req);
	zmq_term(ctx);
	return 0;
}
