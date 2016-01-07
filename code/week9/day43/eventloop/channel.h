#ifndef __CHANNEL_H__

#include <functional>


// TODO: Thinak callback with channel pointer/reference
// Q: can Functor use this?
class Channel {
public:
	typedef std::function<void()> Callback;

	Channel(int fd);
	~Channel();

	void ProcEvent();
	
	int Fd() { return fd_; }
	int Events() { return events_; }
	void SetRevents(int revents) { revents_ = revents; }

	void SetReadCallback(const Callback& cb)
	{ read_callback_ = cb; events_ |= kReadEvent; }
	void SetWriteCallback(const Callback& cb)
	{ write_callback_ = cb; }
	void SetErrorCallback(const Callback& cb)
	{ error_callback_ = cb; }

	bool IsNoneEvent() const { return events_ == kNoneEvent; }

	void enableReading() { events_ |= kReadEvent; }
private:
	static const int kNoneEvent;
	static const int kReadEvent;
	static const int kWriteEvent;

	const int fd_;
	int events_;
	int revents_;

	Callback read_callback_;
	Callback write_callback_;
	Callback error_callback_;
};

#endif // __CHANNEL_H__
