#!/usr/bin/env escript
%% -*- coding:utf-8 -*-

% -mode(compile).

start_rsyncd() ->
    ServerId = 31,
    Path = "path = /data2",
    Conf = lists:flatten(io_lib:format("uid = root~n"
                  "gid = root~n"
                  "use chroot = no~n"
                  "max connections = 10~n"
                  "pid file = /var/run/bada-rsyncd-~p.pid~n"
                  "lock file = /var/run/bada-rsyncd-~p.lock~n"
                  "log file = /var/log/bada-rsync-~p.log~n"
                  "list = no~n"
                  "strict modes = no~n"
                  "#secrets file = /etc/bada-rsyncd.secrets~n"
                  "~n"
                  "[bada-~p]~n"
                  "~p~n"
                  "read only = no~n",
                  [ServerId, ServerId, ServerId, ServerId, Path])),
    Name = lists:flatten(io_lib:format("./bada-rsyncd-~p.conf", [ServerId])),
    io:format("~p~n", [Name]),
    file:write_file(Name, Conf).

main(_) ->
    start_rsyncd().
