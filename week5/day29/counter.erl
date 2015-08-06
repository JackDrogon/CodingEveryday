-module(counter).
-compile(export_all).

dump(K, {counter, N}) -> {counter, N + K}.
read({counter, N}) -> N.
