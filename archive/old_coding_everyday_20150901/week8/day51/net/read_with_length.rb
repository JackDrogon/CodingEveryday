require 'socket'
one_kb = 1024

Socket.tcp_server_loop(4481) do |connection|
  while data = connection.read(one_kb) do
    puts data
  end

  connection.close
end
