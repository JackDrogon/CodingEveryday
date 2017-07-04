-module(timer_observer).
-compile(export_all).

%% TODO restarter
%% TODO Think about use ets

start() ->
    Pid = spawn(fun loop/0),
    register(timer_observer, Pid).

add(Fun, Time) ->
    timer_observer ! {Fun, Time}.

%% FIXME deal with only add fast, so no chance to do
%% Can't do after each add, that so waste
loop() ->
    receive
        {F, T} ->
            spawn(?MODULE, do, [F, T]),
            loop()
    end.

do(F, T) ->
    timer:sleep(T),
    catch(F()).
