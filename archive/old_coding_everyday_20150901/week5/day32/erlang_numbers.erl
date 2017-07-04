#!/usr/bin/env escript
%% -*- coding:utf-8 -*-

print_line(X) ->
    io:format("~p~n", [X]).

print_str_line(X) ->
    io:format("~s~n", [X]).

integer_format() ->
    print_str_line("=========== Erlang Integer Format ==========="),
    print_line(2#10),  % Bin Format
    print_line(16#A0).  % Hex format

operation() ->
    print_str_line("=========== Erlang Integer Operation ==========="),
    print_line(1 + 2),
    print_line(1 - 2),
    print_line(1 * 2),
    print_line(1 / 2),
    print_line(1 div 2),
    print_line(1 rem 2),
    print_line(-1 / 2),
    print_line(-1 div 2),
    print_line(-1 rem 2).

bignumber() ->
    print_str_line("=========== Erlang Big Number ==========="),
    print_line(1111111111111111111111111111111111111111111111).

fac() ->
    ok.

fib() ->
    ok.


main(_) ->
    integer_format(),
    operation(),
    bignumber().
