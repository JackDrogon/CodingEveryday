require 'socket'

Socket.tcp_server_loop(4481) do |connectiton|
  puts connectiton.read 

  connectiton.close
end
