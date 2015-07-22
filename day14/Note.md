1. 感觉写寄存器型的vm还是蛮简单的。接下来要考虑实现if了，没有if就是白搭。还有就是还需要实现float和int的选择。
2. 今天还是看了一些redis的代码。redis的string和hash的field是有冲突的。
3. 学习了一下skiplist的原理和实现。
4. 考虑写一个堆栈式的vm。
5. CPU流水线和预测 cache的实现。
6. 考虑dump出当前运行的内存，这样就是lisp的实现。此处在ruby中可以使用序列化。
7. 考虑如何设计并发模型。
8. Redis和MC一样每个obj都有refcount，用来后台线程做清理和rehash的时候防止被直接删除，这是最简单的GC。
9. VM实现GC。
10. VM添加并发结构。添加各种模型。参考Lua，IO。
11. VM考虑FFI，和使用ruby现有的库。如何结合。参考Clojure, JVM。如何调用操作系统API。
12. 考虑使用JimWimrich的Regex库，来像写那样Yacc，Lex，Lemon一样来写词法解析。此处自己写，然后解析yac
... 参考Antlr。
13. 设计VM的AST。
14. 使用计算的本质的里面的模型，考虑使用规约和类。比如let -> class Let...
