#!/usr/bin/env lua
-- -*- coding:utf-8 -*-

co = coroutine.create(function (a, b, c)
		print("co", a, b, c)
	end)

coroutine.resume(co, 1, 2, 3)

co = coroutine.create(function (a, b)
		coroutine.yield(a+b, a-b)
	end)
print(coroutine.resume(co, 20, 10))

co = coroutine.create(function ()
		print("co", coroutine.yield())
	end)
coroutine.resume(co)
coroutine.resume(co, 4, 5)

co = coroutine.create(function ()
		return 6, 7
	end)
print(coroutine.resume(co))
