require 'socket'

server = TCPServer.new(4481)

Socket.accept_loop(server) do |connetcion|
  # TODO
  connetcion.close
end
