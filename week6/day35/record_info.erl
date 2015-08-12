#!/usr/bin/env escript
%% -*- coding:utf-8 -*-

-record(user, {
         id,
         name,
         email
        }).

main(_) ->
    utils:print_line(record_info(fields, user)).
