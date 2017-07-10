#ifndef __POLLER_H__

#include "poller.h"

#include <vector>
#include <map>
#include <utility>

class Channel;

class PollPoller : public Poller  {
public:
	PollPoller();
	~PollPoller();

private:
	typedef std::vector<struct pollfd> PollFdList;

	PollFdList pollfds_;
	std::vector< std::pair<Channel *, int> > channels_; // pair -> <Channel, Index>, index from pollfds
};

#endif
