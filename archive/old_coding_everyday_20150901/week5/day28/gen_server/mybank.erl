-module(mybank).
-behaviour(gen_server).

%% API
-export([
         start/0,
         start_link/0,
         stop/0,
         new_account/1,
         deposit/2,
         withdraw/2
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

start() ->
    start_link().

start_link() ->
    gen_server:start_link({local, ?SERVER}, ?MODULE, [], []).

stop() ->
    gen_server:call(?MODULE, stop).

new_account(Who)        -> gen_server:call(?MODULE, {new, Who}).
deposit(Who, Amount)    -> gen_server:call(?MODULE, {add, Who, Amount}).
withdraw(Who, Amount)   -> gen_server:call(?MODULE, {remove, Who, Amount}).

%%%===================================================================
%%% gen_server callbacks
%%%===================================================================

init([]) ->
    {ok, ets:new(?MODULE, [])}.

handle_call({new, Who}, _From, Tab) ->
    Reply = case ets:lookup(Tab, Who) of
                []  ->
                    ets:insert(Tab, {Who, 0}),
                      {welcome, Who};
                [_] ->
                    {Who, you_already_are_customer}
            end,
    {reply, Reply, Tab};

handle_call({add, Who, Amount}, _From, Tab) ->
    Reply = case ets:lookup(Tab, Who) of
                [] -> not_a_customer;
                [{Who, Balance}] ->
                    NewBalance = Balance + Amount,
                    ets:insert(Tab, {Who, NewBalance}),
                    {thanks, Who, your_balance_is, NewBalance}
            end,
    {reply, Reply, Tab};

handle_call({remove, Who, Amount}, _From, Tab) ->
    Reply = case ets:lookup(Tab, Who) of
                [] -> not_a_customer;
                [{Who, Balance}] when Amount =< Balance ->
                    NewBalance = Balance - Amount,
                    ets:insert(Tab, {Who, NewBalance}),
                    {thanks, Who, your_balance_is, NewBalance};
                [{Who, Balance}] ->
                    {sorry, Who, you_only_have, Balance, in_the_bank}
            end,
    {reply, Reply, Tab};


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
