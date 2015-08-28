require 'socket'

socket = Socket.new :INET, :STREAM
addr = Socket.pack_sockaddr_in(4481, '0.0.0.0')
socket.bind(addr)
socket.listen(5)

connection, _ = socket.accept

connection.close_read
connection.close_write

__END__
s.shutdown(Socket::SHUT_RD) disallows further read.
s.shutdown(Socket::SHUT_WR) disallows further write.
s.shutdown(Socket::SHUT_RDWR) disallows further read and write.
