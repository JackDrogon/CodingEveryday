-module(timer_observer).
-compile(export_all).

%% TODO restarter
%% TODO Think about use ets

start() ->
    Pid = spawn(fun() -> loop(gb_trees:empty()) end),
    register(timer_observer, Pid).

add(Fun, Time) ->
    timer_observer ! {Fun, Time}.


%% FIXME deal with only add fast, so no chance to do
%% Can't do after each add, that so waste
loop(Elements) ->
    receive
        {F, Time} ->
            {MegaSecs, Secs, MicroSecs} = os:timestamp(),
            T = (MegaSecs * 1000000 + Secs) * 1000000 + MicroSecs + Time,
            case gb_trees:lookup(T, Elements) of
                none ->
                    loop(gb_trees:insert(T, [F], Elements));
                {value, V} ->
                    loop(gb_trees:update(T, [F|V], Elements))
            end
    after 1 ->
              {MegaSecs, Secs, MicroSecs} = os:timestamp(),
              Now = (MegaSecs * 1000000 + Secs) * 1000000 + MicroSecs,
              loop(do(Elements, Now))
    end.

do(Elements, Now) ->
    do(Elements, Now, gb_trees:size(Elements)).

do(Elements, _Now, 0) ->
    Elements;
do(Elements, Now, _Size) ->
    {T, Fs} = gb_trees:smallest(Elements),
    if
        T < Now ->
            % {M, F, A} = F,
            % catch(apply(M, F, A)),
            % io:format("~p~n", [Fs]),
            [spawn(fun() -> catch(F()) end) || F <- Fs],
            gb_trees:delete(T, Elements);
        true ->
            Elements
    end.
