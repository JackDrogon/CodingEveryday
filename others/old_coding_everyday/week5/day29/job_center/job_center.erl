-module(job_center).
-behaviour(gen_server).

%% API
-export([
         start_link/0,
         add_job/1,
         work_wanted/0,
         job_done/1,
         statistics/0
        ]).

%% gen_server callbacks
-export([init/1,
         handle_call/3,
         handle_cast/2,
         handle_info/2,
         terminate/2,
         code_change/3]).

-define(SERVER, ?MODULE).

-record(state, {todo=[], doing=[], done=[], job_count = 0}).

%%%===================================================================
%%% API
%%%===================================================================

start_link() ->
    gen_server:start_link({local, ?SERVER}, ?MODULE, [], []).

add_job(F) ->
    gen_server:call({add, F}).

work_wanted() ->
    gen_server:call({work_wanted}).

job_done(JobNumber) ->
    gen_server:call({job_done, JobNumber}).

statistics() ->
    gen_server:call({statistics}).

%%%===================================================================
%%% gen_server callbacks
%%%===================================================================

init([]) ->
    {ok, #state{}}.

handle_call({add, F}, _From, State = #state{todo = Todo, job_count = JobCount}) ->
    NewJobCount = JobCount + 1,
    NewTodo = [{JobCount, F} | Todo],
    NewState = State#state{todo = NewTodo, job_count = NewJobCount},
    {reply, NewJobCount, NewState};

handle_call({work_wanted}, _From, State = #state{todo = Todo, doing = Doing}) ->
    case length([]) of
        0 ->
            {reply, no, State};
        _ ->
            [Job | NewTodo] = Todo,
            NewDoing = [Job | Doing],
            {reply, Job, State#state{todo = NewTodo, doing = NewDoing}}
    end;

handle_call({job_done, JobNumber}, _From, State = #state{doing = Doing, done = Done, job_count = JobCount}) ->
    if
        JobNumber =< JobCount ->
            case lists:keyfind(JobNumber, 1, Doing) of
                false ->
                    {reply, error, State};
                Job ->
                   NewDoing = lists:delete(Job, Doing),
                   NewDone = [Job | Done],
                   {reply, ok, State#state{doing = NewDoing, done = NewDone}}
            end;
        true ->
            {reply, error, State}
    end;

handle_call({statistics}, _From, State) ->
    {reply, State, State};

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

