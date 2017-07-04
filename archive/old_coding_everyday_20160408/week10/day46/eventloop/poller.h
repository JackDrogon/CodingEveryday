#ifndef __POLLER_H__

#include <vector>
#include <map>
#include <utility>

class Channel;

class Poller {
public:
	typedef std::vector<Channel*> ChannelList;

	Poller();
	~Poller();

	void AddChannel(Channel *channel);
	void Poll(int timeout_ms, ChannelList &fired_channels);
private:
	typedef std::vector<struct pollfd> PollFdList;

	PollFdList pollfds_;
	std::vector<std::pair<Channel *, int> > channels_; // pair -> <Channel, Index>, index from pollfds
};

#endif
