require 'socket'

socket = Socket.new :INET, :STREAM
addr = Socket.pack_sockadd_in(4481, '0.0.0.0')
socket.bind(addr)
