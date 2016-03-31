%%%-------------------------------------------------------------------
%% @doc simple_echo_server public API
%% @end
%%%-------------------------------------------------------------------

-module('simple_echo_server_app').

-behaviour(application).

%% Application callbacks
-export([start/2
        ,stop/1]).

%%====================================================================
%% API
%%====================================================================

start(_StartType, _StartArgs) ->
    'simple_echo_server_sup':start_link().

%%--------------------------------------------------------------------
stop(_State) ->
    ok.

%%====================================================================
%% Internal functions
%%====================================================================
