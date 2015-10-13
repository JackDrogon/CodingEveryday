-module(fifo).
-export([new/0, push/2, pop/1, empty/1]).

%% File: fifo.erl
%% --------------
-spec new() -> {'fifo',[],[]}.
new() -> {'fifo', [], []}.

-spec push({'fifo',_,_},_) -> {'fifo',nonempty_maybe_improper_list(),_}.
push({fifo, In, Out}, X) -> {fifo, [X|In], Out}.


-spec pop({'fifo',_,maybe_improper_list()}) -> {_,{'fifo',_,_}}.
pop({fifo, [], []}) -> erlang:error('empty fifo');
pop({fifo, In, []}) -> pop({fifo, [], lists:reverse(In)});
pop({fifo, In, [H|T]}) -> {H, {fifo, In, T}}.


-spec empty({'fifo',_,_}) -> boolean().
empty({fifo, [], []}) -> true;
empty({fifo, _, _}) -> false.
