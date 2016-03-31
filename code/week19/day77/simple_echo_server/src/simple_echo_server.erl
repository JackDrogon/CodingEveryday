-module(simple_echo_server).
-author('Drogon').

-behaviour(gen_server).

%% API
-export([
         start_link/0,
         start_link/1,
         start_link/2
        ]).

-export([
         start/0,
         start/1,
         start/2
        ]).

%% gen_server callbacks
-export([init/1,
         handle_call/3,
         handle_cast/2,
         handle_info/2,
         terminate/2,
         code_change/3]).

-define(SERVER, ?MODULE).

-record(state, {}).

%%%===================================================================
%%% API
%%%===================================================================

start_link() ->
    gen_server:start_link({local, ?SERVER}, ?MODULE, [], []).
start_link(Port) ->
    gen_server:start_link({local, ?SERVER}, ?MODULE, [Port], []).
start_link(Ip, Port) ->
    gen_server:start_link({local, ?SERVER}, ?MODULE, [Ip, Port], []).

%%%===================================================================
%%% gen_server callbacks
%%%===================================================================

init([]) ->
    process_flag(trap_exit, true),
    proc_lib:spawn_link(?MODULE, start, []),
    {ok, #state{}};
init([Port]) ->
    process_flag(trap_exit, true),
    proc_lib:spawn_link(?MODULE, start, [Port]),
    {ok, #state{}};
init([Ip, Port]) ->
    process_flag(trap_exit, true),
    proc_lib:spawn_link(?MODULE, start, [Ip, Port]),
    {ok, #state{}}.

handle_call(_Request, _From, State) ->
    Reply = ok,
    {reply, Reply, State}.

handle_cast(_Msg, State) ->
    {noreply, State}.

handle_info(_Info, State) ->
    {noreply, State}.

terminate(_Reason, _State) ->
    ok.

code_change(_OldVsn, State, _Extra) ->
    {ok, State}.

%%%===================================================================
%%% Internal functions
%%%===================================================================

%% API
%%% @doc: a simple echo server with accept_loop_pool

%% TODO: add gen_server, monitor, supervisor
%% TODO: add tcp rst deal
%% TODO: send nodelay
%% TODO: Change the process_pool
%% TODO: Use larger
%% TODO: Follow the otp application 
%% TODO: Erlang eambeed
%% TODO: Add EUnit
%% TODO: Cross with elixir

ip_to_string(IP) ->
    {A, B, C, D} = IP,
    lists:flatten(io_lib:format("~p.~p.~p.~p", [A, B, C, D])).

start() ->
    start(1234).

start(Port) ->
    start({127, 0, 0, 1}, Port).

start(IP, Port) ->
    Option = [binary, {packet, 0}, {reuseaddr, true}, {active, true}, {ip, IP}],
    % Option = [binary, {packet, 0}, {reuseaddr, true}, {ip, {127, 0, 0, 1}}, {active, true}],
    io:format("Listening on ~s:~p.~n", [ip_to_string(IP), Port]),
    {ok, Listen} = gen_tcp:listen(Port, Option),
    % spawn(fun() -> accept_loop(Listen) end).
    accept_loop_pool(Listen, 4).

accept_loop_pool(Listen, 1) ->
    accept_loop(Listen);
accept_loop_pool(Listen, N) ->
    spawn(fun() -> accept_loop(Listen) end),
    accept_loop_pool(Listen, N-1).

accept_loop(Listen) ->
    {ok, Socket} = gen_tcp:accept(Listen),
    {ok, {Address, Port}} = inet:peername(Socket),
    inet:setopts(Socket, [{nodelay, true}]),
    Pid = spawn(fun() -> echo_loop(Socket, {Address, Port}) end),
    gen_tcp:controlling_process(Socket, Pid),
    io:format("*** ~s:~p connected, deal with Pid:~p.~n", [ip_to_string(Address), Port, Pid]),
    accept_loop(Listen).

echo_loop(Socket, {Address, Port}) ->
    receive
        {tcp, Socket, Bin} ->
            io:format("~s", [Bin]),
            gen_tcp:send(Socket, Bin),
            echo_loop(Socket, {Address, Port});
        % TODO: add tcp_passive tcp_error deal
        {tcp_passive, Socket} ->
            ok;
        {tcp_closed, Socket} ->
            io:format("*** ~s:~p disconnected.~n", [ip_to_string(Address), Port]),
            gen_tcp:close(Socket);
        {tcp_error, Socket, Reason} ->
            io:format("TcpError: ~p~n.", [Reason])
    end.
