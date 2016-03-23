-module(honey_log).
-compile(export_all).
-author("Dmitry Podkorytov").

%more about disk_log see http://www.erlang.org/doc/man/disk_log.html

open(Name)->
    disk_log:open
    ([{name,Name},
      {file, atom_to_list(?MODULE)++".log"},
      % | {linkto, LinkTo :: none | pid()}
      % | {repair, Repair :: true | false | truncate}

      %  {type, wrap },
      %  {format, external },
      {size, 10000000},
      % | {distributed, Nodes :: [node()]}
      % | {notify, boolean()}
      % | {head, Head :: dlog_head_opt()}
      % | {head_func, MFA :: {atom(), atom(), list()}}
      {mode, read_write}
     ]).

con_log(A,B,C,D)-> con_log({A,B,C,D}).

con_log(Msg)-> io:format(" ~p.~n",[{date(),time(),Msg}]).

log(Log,Term)-> disk_log:log(Log,Term).

test()->
    {ok,Log}=open(?MODULE),

    io:format("Log=~p ~n",[Log]),
    [
     log(Log,{date(),time(),1}),
     log(Log,{date(),time(),2}),
     disk_log:sync(Log),
     disk_log:info(Log),
     disk_log:chunk(Log,start),
     chunks(Log),
     disk_log:close(Log),
     disk_log:accessible_logs()
    ].

chunks(Log)->chunks(Log,start).

chunks(Log,Ch)->
    R=disk_log:chunk(Log,Ch),
    %io:format("~p:~p ~p ~n",[?MODULE,?LINE,R]),
    case R of
        eof->[];
        {Ch1,List}->[List|chunks(Log,Ch1)]
    end.

% probably in future will needs calls functions wrap_log_reader module for reading segmented logs.
