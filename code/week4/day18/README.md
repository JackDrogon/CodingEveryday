### Today is 2015-10-20, Tue.

#### My Code
1. insert_sort_for_otool_usage.c
2. leveldb_utils.cc
3. linux_userspace_crypto.c
4. tail.tcl
5. timestamp_vs_now.erl timestamp_vs_now_concurrent.erl

此处erlang的比较使用escript，escript开启了`-mode(compile)`, 性能有较大提高，比较接近erlang编译后。但是concurrent的erlang:now性能竟然和之前一样，可见锁的威力太大了...
