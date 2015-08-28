require 'socket'

socket = Socket.new :INET, :STREAM
addr = Socket.pack_sockaddr_in(4481, '0.0.0.0')
socket.bind(addr)
socket.listen(5)

connection, _ = socket.accept
