require 'socket'

socket = TCPSocket.new 'baidu.com', 80
opt = socket.getsockopt Socket::SOL_SOCKET, Socket::SO_TYPE:w

opt.int == Socket::SOCK_STREAM
opt.int == Socket::SOCK_DGRAM
