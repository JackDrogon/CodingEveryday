-module(utils).
-author('Drogon').

-export([
         print_line/1,
         print_str_line/1,
         pid_status/1
        ]).

print_line(X) ->
    io:format("~p~n", [X]).

print_str_line(X) ->
    io:format("~s~n", [X]).

pid_status(Pid) ->
    sys:get_status(Pid).
