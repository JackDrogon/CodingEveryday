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

arithmetic_operation() ->
    print_str_line("=========== Erlang Number Arithmetic Operation ==========="),
    print_line(1 + 2),      % 3
    print_line(1 - 2),      % -1
    print_line(1 * 2),      % 2
    print_line(1 / 2),      % 0.5
    print_line(1 div 2),    % 0
    print_line(1 rem 2),    % 1
    print_line(-1 / 2),     % -0.5
    print_line(-1 div 2),   % 0
    print_line(-1 rem 2).   % -1

bit_operation() ->
    print_str_line("=========== Erlang Number Bit Operation ==========="),
    %% band是按位与运算，bor是按位或运算，bxor是按位异或，bsl按位左移，bsr按位右移，注意最后的结果都是二进制。
    print_line(2#10 band 2#110),    % 2 => 2#10
    print_line(2#10 bor 2#100),     % 6 => 2#110
    print_line(2#10 bxor 2#11),     % 1 => 2#1
    print_line(2#10 bsl 2),         % 8 => 2#1000
    print_line(2#10 bsr 2).         % 0 => 2#0

logic_operation() ->
    print_str_line("=========== Erlang Logic Operation ==========="),
    %%  四个，not，and，or，xor
    print_line(not true),           % false
    print_line(true and false),     % false
    print_line(true xor false),     % true
    print_line(true or false).      % true

list_operation() ->
    %% ++, --
    print_str_line("=========== Erlang List Operation ==========="),
    print_line([1,2] ++ [3,4]),
    print_line([1,2] -- [3,4]),
    print_line([1,2] -- [1,4]),
    print_line([1,2] ++ [1,4]),
    print_line([1,2] -- [1,2]),
    print_line([1,2] -- [2,1]),
    print_line([1,2,1] -- [2,1]).

comparison_operation() ->
    %% < =< = >= == =:= /= =/=
    %% number < atom < reference < fun < port < pid < tuple < list < bit string
    ok.

bignumber() ->
    print_str_line("=========== Erlang Big Number ==========="),
    print_line(1111111111111111111111111111111111111111111111).

fac() ->
    ok.

fib() ->
    ok.


main(_) ->
    integer_format(),
    arithmetic_operation(),
    bit_operation(),
    logic_operation(),
    list_operation(),
    bignumber().
