#include "Channel.h"

#include <cassert>
#include <poll.h>

const int Channel::kNoneEvent = 0;
const int Channel::kReadEvent = POLLIN | POLLPRI;
const int Channel::kWriteEvent = POLLOUT;

Channel::Channel(int fd) : fd_(fd), events_(kNoneEvent), revents_(0)
{
	assert(fd >= 0);
}

Channel::~Channel()
{
}

void Channel::ProcEvent()
{
	// TODO: Thinak about poll error, callback = NULL
	if (revents_ & POLLNVAL) {
		/* LOG_WARN << "Channel::handle_event() POLLNVAL"; */
	}

	if (revents_ & (POLLERR | POLLNVAL)) {
		if (error_callback_) error_callback_();
	}
	/* if (revents_ & (POLLIN | POLLPRI | POLLRDHUP)) {  POLLRDHUP POLLRDHUP (since Linux 2.6.17) */
	if (revents_ & (POLLIN | POLLPRI)) {
		if (read_callback_) read_callback_();
	}
	if (revents_ & POLLOUT) {
		if (write_callback_) write_callback_();
	}
}
