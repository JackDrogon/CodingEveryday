#!/usr/bin/env escript
%% -*- coding:utf-8 -*-

main(_) ->
    R = honey_log:test(),
    io:format("~p~n", [R]).
