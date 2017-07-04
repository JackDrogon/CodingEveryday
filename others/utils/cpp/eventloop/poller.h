#pragma once

#include <vector>

class Eventloop;
class Channel;

class Poller {
public:
	typedef std::vector<Channel*> ChannelList;

	Poller() {}
	virtual ~Poller() {}

	virtual void Poll(int timeout_ms, ChannelList &fired_channels) = 0;

	virtual void AddChannel(Channel *channel) = 0;
	virtual void RemoveChannel(Channel *channel) = 0;
	virtual void ModifyChannel(ChannelList *channel) = 0;

	virtual void Fork() = 0;
};
