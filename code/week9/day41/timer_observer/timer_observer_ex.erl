#!/usr/bin/env escript
%% -*- coding:utf-8 -*-

main(_) ->
    timer_observer:start(),
    timer_observer:add(fun() -> io:format("3~n") end, 3),
    timer_observer:add(fun() -> io:format("1~n") end, 1),
    timer_observer:add(fun() -> io:format("another 1~n") end, 1),
    timer_observer:add(fun() -> io:format("40~n") end, 40),
    timer_observer:add(fun() -> io:format("4000~n") end, 4000),
    timer:sleep(4500),
    halt(0).
