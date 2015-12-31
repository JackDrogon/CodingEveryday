%%%-------------------------------------------------------------------
%% @doc tcp_proxy top level supervisor.
%% @end
%%%-------------------------------------------------------------------

-module('tcp_proxy_sup').

-behaviour(supervisor).

%% API
-export([start_link/0]).

%% Supervisor callbacks
-export([init/1]).

-define(SERVER, ?MODULE).

%%====================================================================
%% API functions
%%====================================================================

start_link() ->
    supervisor:start_link({local, ?SERVER}, ?MODULE, []).

%%====================================================================
%% Supervisor callbacks
%%====================================================================

%% Child :: {Id,StartFunc,Restart,Shutdown,Type,Modules}
init([]) ->
    SupFlags = #{strategy => one_for_one, intensity => 0, period => 1},
    ChildSpecs = [#{id => tcp_proxy,
                    start => {tcp_proxy, start, []},
                    restart => permanent,
                    shutdown => 2000,
                    type => worker,
                    modules => [tcp_proxy]}],
    {ok, {SupFlags, ChildSpecs}}.



%%====================================================================
%% Internal functions
%%====================================================================
