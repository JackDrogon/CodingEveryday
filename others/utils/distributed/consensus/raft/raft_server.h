#ifndef RAFT_SERVER_H_
#define RAFT_SERVER_H_

class RaftServer {
private:
	int id_;

	// @doc: durable
	int current_term_;
	int vote_for_;
	// log[]

	// @doc: changable
	int commit_index_;
	int last_applied_;

};

#endif // RAFT_SERVER_H_
