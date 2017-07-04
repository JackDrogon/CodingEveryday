#ifndef __EVENT_LOOP__

#include "channel.h"
#include "poller.h"
#include <vector>

class Channel;

class EventLoop {
public:
	EventLoop();
	~EventLoop();
	
	void AddChannel(Channel *channel);

	void Loop();
	void Quit();

private:
	typedef std::vector<Channel*> ChannelList;

	bool quit_;
	ChannelList fired_channels_;
	Poller poller_;
};

#endif
