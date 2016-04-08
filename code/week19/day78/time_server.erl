-module(time_server).

-behaviour(gen_server).

%% API
-export([
         start_link/0,
         accept_loop/1
        ]).

%% gen_server callbacks
-export([init/1,
         handle_call/3,
         handle_cast/2,
         handle_info/2,
         terminate/2,
         code_change/3]).

-define(SERVER, ?MODULE).
-define(TCP_OPTIONS, [binary, {packet, 0}, {active, false}, {reuseaddr, true}]).

-record(server_state, {lsocket}).

%%%===================================================================
%%% API
%%%===================================================================

start_link() ->
    gen_server:start_link({local, ?SERVER}, ?MODULE, 1234, []).

%%%===================================================================
%%% gen_server callbacks
%%%===================================================================

init(Port) ->
    case gen_tcp:listen(Port, ?TCP_OPTIONS) of
        {ok, LSocket} ->
            State = #server_state{lsocket = LSocket},
            {ok, accept(State)};
        {error, Reason} ->
            {stop, Reason}
    end.

handle_call(_Request, _From, State) ->
    Reply = ok,
    {reply, Reply, State}.

handle_cast({accepted, _Pid}, State=#server_state{}) ->
    {noreply, accept(State)}.

handle_info(_Info, State) ->
    {noreply, State}.

terminate(_Reason, _State) ->
    ok.

code_change(_OldVsn, State, _Extra) ->
    {ok, State}.

%%%===================================================================
%%% Internal functions
%%%===================================================================

time_now() ->
    {_, _, Usec} = Now = os:timestamp(),
    {{Y, Mo, D}, {H, Mi, S}} = calendar:now_to_datetime(Now),
    io_lib:format("~4.4.0w-~2.2.0w-~2.2.0wT~2.2.0w:~2.2.0w:~2.2.0w.~6.6.0w", [ Y, Mo, D, H, Mi, S, Usec ]).

accept(#server_state{lsocket = LSocket} = State) ->
    proc_lib:spawn(?MODULE, accept_loop, [{self(), LSocket}]),
    State.
accept_loop({Server, LSocket}) ->
    {ok, Socket} = gen_tcp:accept(LSocket),
    gen_server:cast(Server, {accepted, self()}),
    gen_tcp:send(Socket, time_now()),
    gen_tcp:close(Socket).
