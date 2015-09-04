-module(utils).
-author('Drogon').

-export([
         print_line/1
        ]).

print_line(X) ->
    io:format("~p~n", [X]).
