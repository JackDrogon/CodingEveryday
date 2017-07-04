#!/usr/bin/env escript
%% -*- coding:utf-8 -*-
%%! -pa ../../others/utils/erlang/ebin/

-import(utils, [print_line/1, print_str_line/1]).

binary_nif() ->
    A = <<"Hello, World!">>,
    print_line([binary:at(A, 0)]),
    % print_line([binary:at(A, 100)]).  exception error: bad argument

    %% bin_to_list(Subject, {0,byte_size(Subject)}).
    print_line(binary:bin_to_list(<<"erlang">>)),
    print_line(binary:bin_to_list(<<"erlang">>, {1,3})).

main(_) ->
    binary_nif().
