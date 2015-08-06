#!/usr/bin/env escript
%% -*- coding:utf-8 -*-


print(S) ->
    io:format("~p~n", [S]).

main(_) ->
    C = {counter, 2},
    print(C:read()),
    C1 = C:dump(3),
    print(C1),
    print(C1:read()).
