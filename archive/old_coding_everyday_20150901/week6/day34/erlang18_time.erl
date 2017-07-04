#!/usr/bin/env escript
%% -*- coding:utf-8 -*-

print_line(X) ->
    io:format("~p~n", [X]).

main(_) ->
    print_line(os:timestamp()),
    print_line(erlang:system_time()).
