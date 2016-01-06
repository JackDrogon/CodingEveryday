#ifndef __NIO_H__
#define __NIO_H__

#include <unistd.h>

ssize_t readn(int fd, void *vptr, size_t n);
ssize_t writen(int fd, const void *vptr, size_t nbytes);
ssize_t readline(int fd, void *vptr, size_t maxlen);

#endif // __NIO_H__
