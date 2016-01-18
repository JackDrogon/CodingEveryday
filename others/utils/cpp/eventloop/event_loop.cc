#include "event_loop.h"

#include <cstdlib>
#include <cassert>
#include <poll.h>

// TODO: AddChannel use std::move

__thread EventLoop* t_loopInThisThread = nullptr;

EventLoop::EventLoop() : quit_(false)
{
	assert(t_loopInThisThread == nullptr);
	t_loopInThisThread = this;
}

EventLoop::~EventLoop()
{
}

void EventLoop::AddChannel(Channel *channel)
{
	poller_.AddChannel(channel);
}

void EventLoop::Loop()
{
	quit_ = false;
	while (!quit_) {
		/* ::poll(NULL, 0, 3*1000); */
		fired_channels_.clear();
		poller_.Poll(1000, fired_channels_);
		for (auto active_channel = fired_channels_.begin();
				active_channel != fired_channels_.end();
				++active_channel) {
			(*active_channel)->ProcEvent();
		}
	}
}

void EventLoop::Quit()
{
	quit_ = true;
}
