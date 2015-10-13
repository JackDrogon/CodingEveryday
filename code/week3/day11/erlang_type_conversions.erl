#!/usr/bin/env escript
%% -*- coding:utf-8 -*-

-import(utils, [print_line/1]).

%%% atom_to_binary/2, atom_to_list/1, binary_to_atom/2, binary_to_existing_atom/2, binary_to_list/1, bitstring_to_list/1, binary_to_term/1, float_to_list/1, fun_to_list/1, integer_to_list/1, integer_to_list/2, iolist_to_binary/1, iolist_to_atom/1, list_to_atom/1, list_to_binary/1, list_to_bitstring/1, list_to_existing_atom/1, list_to_float/1, list_to_integer/2, list_to_pid/1, list_to_tuple/1, pid_to_list/1, port_to_list/1, ref_to_list/1, term_to_binary/1, term_to_binary/2 and tuple_to_list/1.

main(_) ->
    print_line(list_to_integer("54")),
    print_line(integer_to_list(54)),

    print_line(list_to_float("54.32")),

    print_line(atom_to_list(true)),

    print_line(list_to_bitstring("hi there")),
    print_line(bitstring_to_list(<<"hi there">>)).
