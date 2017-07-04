#!/usr/bin/env escript

-mode(compile).

epoch() ->
    {Mega,Sec,Mili} = now(),
    (Mega * 1000000) + Sec + (Mili / 1000000).

measure(F) ->
    Ini = epoch(),
    F(),
    epoch() - Ini.

waiting() ->
    receive
        _ -> waiting()
    after 500 ->
              ok
    end.

launch(M,F) ->
    Times = lists:seq(1,25000),
    monitor(process, spawn(fun() -> [ M:F() || _ <- Times ] end)).

main(_Args) ->
    Times = lists:seq(1,1000),
    Test1 = fun() -> [ launch(os, timestamp) || _ <- Times ], waiting() end,
    Test2 = fun() -> [ launch(erlang, now) || _ <- Times ], waiting() end,
    io:format("os:timestamp = ~5.2f ~5.2f ~5.2f~n", [
                                                     measure(Test1), measure(Test1), measure(Test1)
                                                    ]),
    io:format("erlang:now   = ~5.2f ~5.2f ~5.2f~n", [
                                                     measure(Test2), measure(Test2), measure(Test2)
                                                    ]),
    0.
