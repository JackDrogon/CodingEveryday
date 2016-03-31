1. genserver && gentcp合体模式
2. 这里面有一个我卡了不少时间，我原来的`simple_echo_server:start_link()` 中间接调用了start，但是start会在调用accept pool等于0的时候退出，导致原来的socket也会被close，我不清楚一个process创建的socket，会在process死亡的时候被close。
