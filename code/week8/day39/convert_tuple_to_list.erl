#!/usr/bin/env escript
%% -*- coding:utf-8 -*-

-spec convert_tuple_to_list(tuple()) -> list().
convert_tuple_to_list(Tuple) ->
    convert_tuple_to_list(1, size(Tuple),Tuple, []).

%%% @doc: Add Tuple[Nth] => List, Nth >= 1
-spec convert_tuple_to_list(integer(), integer(), tuple(), list()) -> list().
convert_tuple_to_list(Nth, Size, Tuple, List) when Nth =< Size ->
    convert_tuple_to_list(Nth+1, Size, Tuple, [erlang:element(Nth, Tuple) | List]);
convert_tuple_to_list(_Nth, _Size, _Tuple, List) ->
    lists:reverse(List).

main(_) ->
    T = {1, 2, 3, 4},
    io:format("~p~n", [T]),
    L = convert_tuple_to_list(T),
    io:format("~p~n", [L]).
