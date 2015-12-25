#!/usr/bin/env escript
%% -*- coding:utf-8 -*-

main(_) ->
    timer_observer:start(),
    timer_observer:add(fun() -> io:format("3~n") end, 3),
    timer_observer:add(fun() -> io:format("1~n") end, 1),
    timer_observer:add(fun() -> io:format("another 1~n") end, 1),
    timer_observer:add(fun() -> io:format("40~n") end, 40),
    timer:sleep(300),
    halt(0).
