#include "Poller.h"

#include "channel.h"
#include <vector>
#include <cassert>
#include <poll.h>
#include <iostream>


Poller::Poller()
{
}

Poller::~Poller()
{
}

void Poller::AddChannel(Channel *channel)
{
	// TODO: bzero resize vector
	// TODO: when to reduce channel size
	int fd = channel->Fd();
	if (static_cast<int>(channels_.size()) < fd || channels_[fd].first == NULL) {
		// a new one, add to pollfds_
		/* assert(channels_.find(channel.fd()) == channels_.end()); */
		struct pollfd pfd;
		pfd.fd = fd;
		pfd.events = static_cast<short>(channel->Events());
		pfd.revents = 0;

		/* pollfds_.resize(fd+1); */
		/* pollfds_[fd] = pfd; */
		pollfds_.push_back(pfd);

		channels_.resize(fd+1, std::make_pair<Channel*, int>(NULL, -1));
		// channels_[fd] = std::make_pair<Channel*, int>(channel, static_cast<int>(pollfds_.size())-1); 直接用Channel竟然不行
		channels_[fd] = std::make_pair<Channel*, int>(&*channel, static_cast<int>(pollfds_.size())-1);
	} else {
		// update existing one
		struct pollfd& pfd = pollfds_[channels_[fd].second];
		pfd.events = static_cast<short>(channel->Events());
		pfd.revents = 0;
		if (channel->IsNoneEvent()) {
			// ignore this pollfd
			pfd.fd = -1;
		}
	}
}

void Poller::Poll(int timeout_ms, ChannelList &fired_channels)
{
	int num_events = ::poll(&*pollfds_.begin(), pollfds_.size(), timeout_ms);

	std::cout << "Num Events: " << num_events << std::endl;

	if (num_events > 0) {
		/* fired_channels.resize(num_events); */
		fired_channels.clear();
		for (PollFdList::const_iterator pfd = pollfds_.begin();
				pfd != pollfds_.end(); ++pfd) {
			Channel* channel = channels_[pfd->fd].first;
			channel->SetRevents(pfd->revents);
			fired_channels.push_back(channel);
		}
	}
}
