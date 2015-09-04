flush_buffer() ->
	receive
		_Any ->
			flush_buffer()
	after 0 ->
		true
	end.


priority_reveive() ->
	receive
		{alarm, X} ->
			{alarm, X}
	after 0 ->
		receive
			Any ->
				Any
			end
	end.



start_nano_server() ->
	{ok, Listen} = gen_tcp:listen(Port, [binary, {packet, 4},
								  {reuseaddr, true},
								  {active, true}]),
	{ok, Socket} = gen_tcp:accept(Listen),
	gen_tcp:close(Listen),
	loop(Socket).

loop(Socket) ->
	receive
		{tcp, Socket, Bin} ->
			%% TODO: Do_Somthing Bin => Replay
			gen_tcp:send(Socket, term_to_binary(Reply)),
			loop(Socket);
		{tcp_closed, Socket} ->
			io:format("Sever socket closed~n")
	end.


nano_client(Str) ->
	{Ok, Socket} =
		gen_tcp:connect(Ip, Port, [binary, {packet. 4}]),
	ok = gen_tcp:send(Socket, term_to_binary(Str)),
	receive
		{tcp, Socket, Bin} ->
			%% TODO: Do_Somthing Bin
		gen_tcp:close(Socket)
	end.

	{O}
	par_connect(Listen)

keep_alive(Name, Fun) ->
	register(Name, Pid = spawn(Fun)),
	on


do_rpc(Socket, RawData) ->
    try
        {M, F, A} = split_out_mfa(RawData),
        Result = apply(M, F, A),
        gen_tcp:send(Socket, io_lib:fwrite("~p~n", [Result]))
    catch
        _Class:Err ->
            gen_tcp:send(Socket, io_lib:fwrite("~p~n", [Err]))
    end.

split_out_mfa(RawData) ->
    MFA = re:replace(RawData, "\r\n$", "", [{return, list}]),
    {match, [M, F, A]} =
        re:run(MFA,
               "(.*):(.*)\s*\\((.*)\s*\\)\s*.\s*$",
                   [{capture, [1,2,3], list}, ungreedy]),
    {list_to_atom(M), list_to_atom(F), args_to_terms(A)}.

args_to_terms(RawArgs) ->
    {ok, Toks, _Line} = erl_scan:string("[" ++ RawArgs ++ "]. ", 1),
    {ok, Args} = erl_parse:parse_term(Toks),
    Args.
