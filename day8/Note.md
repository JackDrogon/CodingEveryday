Observer
Elixir can use function as function's params.
So I maintain a list which contains function registered for event.
When event come along, I just need to run the function in list.

在做Elixir的编译的时候，发现一件事情，在module之外的地方写代码，会被运行，但是如果是spwan了一个进程，进程会在 编译结束的时候，被强迫结束。
