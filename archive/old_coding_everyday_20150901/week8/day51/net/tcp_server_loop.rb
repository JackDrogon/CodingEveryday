require 'socket'

Socket.tcp_server_loop(4481) do |connection|
  # TODO
  connection.close
end
