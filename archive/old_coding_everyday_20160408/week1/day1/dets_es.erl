#!/usr/bin/env escript
%% -*- coding:utf-8 -*-

dets_open_test() ->
    {ok, Tab} = dets:open_file("food").

dets_test() ->
    dets:open_file(food, [{type, bag}, {file, "./food"}]),
    dets:insert(food, {italy, spaghetti}),
    dets:insert(food, {italy, rice}),
    dets:insert(food, {sweden, meatballs}),
    io:format("Lookup china: ~p~n", [dets:lookup(food, china)]),
    io:format("Lookup italy: ~p~n", [dets:lookup(food, italy)]),
    io:format("Lookup sweden: ~p~n", [dets:lookup(food, sweden)]),
    dets:close(food).

traverse_test() ->
    dets:open_file(food, [{type, bag}, {file, "./food"}]),
    Fun = fun(X) -> io:format("~p~n", [X]), continue end,
    dets:traverse(food, Fun).

main(_) ->
    dets_test(),
    traverse_test().
