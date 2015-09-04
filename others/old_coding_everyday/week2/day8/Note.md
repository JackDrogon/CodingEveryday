Observer
Elixir can use function as function's params.
So I maintain a list which contains function registered for event.
When event come along, I just need to run the function in list.

Elixir的Process的register不是BIF形式的，也就是说不是Kernel包里面的，而是在Process里面。而且send函数使用起来没有Erlang的!感觉爽。 send -> !, register -> Process.register, receive -> receive。

在做Elixir的编译的时候，发现一件事情，在module之外的地方写代码，会被运行，但是如果是spwan了一个进程，进程会在 编译结束的时候，被强迫结束。
