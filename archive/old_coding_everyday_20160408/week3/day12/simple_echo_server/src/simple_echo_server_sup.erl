%%%-------------------------------------------------------------------
%% @doc simple_echo_server top level supervisor.
%% @end
%%%-------------------------------------------------------------------

-module('simple_echo_server_sup').

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
    ChildSpecs = [#{id => simple_echo_server,
                    start => {simple_echo_server, start, []},
                    restart => permanent,
                    shutdown => 2000,
                    type => worker,
                    modules => [simple_echo_server]}],
    {ok, {SupFlags, ChildSpecs}}.

%%====================================================================
%% Internal functions
%%====================================================================
