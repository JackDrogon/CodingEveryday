## Note

### Erlang
#### 几天使用Erlang的时候还是感觉卡了一下
1. list tuplelist的使用
```
lists:keyfind
lists:delete
```

2. record用法

3. if 和 case的区别
case 的分支是对同一个结果进行比较
然而if是对同一个进行比较
此处和C语言没什么太大的却别，case相对于switch而言

4. erlang的 小于等于比较奇葩 是 =<

5. erlang group leader

6. erlang crash.logr如何分析

7.erlang sasl errol指定文件


### xargs
find . -size +50M -print0 | xargs -0 -I {} cp {} largefolder/
使用-I参数，后面跟的符号表明用该符号替代find传递过来的值。

```shell
$ man xargs

-I replace-str
              Replace occurrences of replace-str in the initial-arguments with
              names read from standard input.  Also, unquoted  blanks  do  not
              terminate  input  items;  instead  the  separator is the newline
              character.  Implies -x and -L 1.
```

### Vim Tabular

1. 假如我想让其中的两行按等号对齐，则将光标定位到有等号的那行，执行 `:Tab /=` 即可。

2. 又如，若想将下面的

    ```
    |1|2|
    |one|two|
    ```
    变成
    
    ```
    | 1 | 2 |
    | one | two |
    ```
    可执行 `:Tab /|`。

