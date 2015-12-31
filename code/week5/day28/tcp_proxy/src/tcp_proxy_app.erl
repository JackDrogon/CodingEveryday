%%%-------------------------------------------------------------------
%% @doc tcp_proxy public API
%% @end
%%%-------------------------------------------------------------------

-module('tcp_proxy_app').

-behaviour(application).

%% Application callbacks
-export([start/2
        ,stop/1]).

%%====================================================================
%% API
%%====================================================================

start(_StartType, _StartArgs) ->
    'tcp_proxy_sup':start_link().

%%--------------------------------------------------------------------
stop(_State) ->
    ok.

%%====================================================================
%% Internal functions
%%====================================================================
