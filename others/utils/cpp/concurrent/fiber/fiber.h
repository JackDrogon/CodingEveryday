#ifndef FIBRT_H_
#define FIBRT_H_

#include <functional>
#include <ucontext.h>

class Scheduler;

class Fiber {
public:
	typedef void (*Func)(Fiber *);
	friend class Scheduler;
	enum Status { kDead, kReady, kRunning, kSuspend };
	using Event = std::function<void()>;

	Fiber(Scheduler& scheduler, Event event);
	~Fiber();

	void Resume();
	bool Status();
	void SetFid(uint64_t fid) { fid_ = fid; }

private:
	uint64_t fid_;
	Scheduler& scheduler_;
	Event event_;
	enum Status status_;
	ucontext_t context_;
	ucontext_t* main_context_;
	Func main_;
	
	const static int STACK_SIZE = 4096;
	char stack_[STACK_SIZE];

	void Run();
	// void SetMain(Event main_event) { main_ = main_event; }
};

#endif // FIBRT_H_
