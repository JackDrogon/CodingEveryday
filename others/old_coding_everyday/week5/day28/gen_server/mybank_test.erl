#!/usr/bin/env escript
%% -*- coding:utf-8 -*-

main(_) ->
  mybank:start(), % {ok,<0.35.0>}
  mybank:deposit("joe", 10),  % not_a_customer
  mybank:new_account("joe"),  % {welcome,"joe"}
  mybank:deposit("joe", 10),  % {thanks,"joe",your_balance_is,10}
  mybank:withdraw("joe", 15),  % {sorry,"joe",you_only_have,10,in_the_bank}
  mybank:deposit("joe", 30),  % {thanks,"joe",your_balance_is,40}
  mybank:deposit("joe", 15),  % {thanks,"joe",your_balance_is,55}
  mybank:withdraw("joe", 20).  % {thanks,"joe",your_balance_is,35}
