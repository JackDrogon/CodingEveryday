#!/usr/bin/env escript

-mode(compile).

epoch() ->
    {Mega,Sec,Mili} = now(),
    (Mega * 1000000) + Sec + (Mili / 1000000).

measure(F) ->
    Ini = epoch(),
    F(),
    epoch() - Ini.

main(_Args) ->
    Times = lists:seq(1,1000000),
    Test1 = fun() -> [ os:timestamp() || _ <- Times ] end,
    Test2 = fun() -> [ now() || _ <- Times ] end,
    io:format("os:timestamp = ~5.2f ~5.2f ~5.2f~n", [
                                                     measure(Test1), measure(Test1), measure(Test1)
                                                    ]),
    io:format("erlang:now   = ~5.2f ~5.2f ~5.2f~n", [
                                                     measure(Test2), measure(Test2), measure(Test2)
                                                    ]),
    0.
