#include "async_log_device.h"
#include "buffer.h"

#define fwrite_unlocked fwrite

const int AsyncLogDevice::BUFFER_SIZE = 4 << 20;

AsyncLogDevice::AsyncLogDevice(FILE *handle) :
	handle_(handle),
	current_buffer_(nullptr),
	next_buffer_(nullptr),
	empty_buffers_(),
	write_buffers_(),
	write_mutex_(),
	write_condv_(),
	thread_quit_(false),
	write_worker_(std::thread(&AsyncLogDevice::write_file_, this))
{
	current_buffer_ = new Buffer(BUFFER_SIZE);
	next_buffer_ = new Buffer(BUFFER_SIZE);
}

AsyncLogDevice::~AsyncLogDevice()
{
	thread_quit_ = true;
	write_worker_.join();
	fclose(handle_);
}

void AsyncLogDevice::Append(const std::string &msg)
{
	Append(msg.data(), msg.size());
}

void AsyncLogDevice::Append(const char *msg, const size_t size)
{
	// size > buffer size
	std::lock_guard<std::mutex> mutex_guard(mutex_);
	if (current_buffer_->Avail() > size) {
		current_buffer_->Append(msg, size);
	} else {
		{
			std::unique_lock<std::mutex> ul(write_mutex_);
			write_buffers_.push(current_buffer_);
			current_buffer_ = next_buffer_;
			if (empty_buffers_.size()) {
				current_buffer_ = empty_buffers_.top();
				empty_buffers_.pop();
			} else {
				current_buffer_ = new Buffer(BUFFER_SIZE);
			}
		}
		write_condv_.notify_one();
		current_buffer_->Append(msg, size);
	}
}

// fwrite_unlocked(msg.data(), 1, msg.size(), handle_);


void AsyncLogDevice::Flush()
{
	// TODO
}

void AsyncLogDevice::write_file_()
{
	Buffer* write_buffer(nullptr);
	while (true) {
		if (thread_quit_) {
			std::lock_guard<std::mutex> w_lg(write_mutex_);
			std::lock_guard<std::mutex> lg(mutex_);

			write_buffers_.push(current_buffer_);
			while(write_buffers_.size()) {
				write_buffer = write_buffers_.front();
				write_buffers_.pop();
				fwrite_unlocked(write_buffer->Data(), 1, write_buffer->Size(), handle_);
			}

			break;
		}

		{
			std::unique_lock<std::mutex> ul(write_mutex_);
			write_condv_.wait(ul, [&]{ return write_buffers_.size(); });
			
			write_buffer = write_buffers_.front();
			write_buffers_.pop();
		}

		fwrite_unlocked(write_buffer->Data(), 1, write_buffer->Size(), handle_);

		std::unique_lock<std::mutex> ul(write_mutex_);
		write_buffer->Clear();
		empty_buffers_.push(write_buffer);
		write_buffer = nullptr;
	}
}
