#!/usr/bin/env python
# encoding: utf-8

import socket, time, os, sys

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((sys.argv[1], 8888))
sock.send(os.getlogin() + '\n')
message = sock.recv(4096)
print message
sock.close()
