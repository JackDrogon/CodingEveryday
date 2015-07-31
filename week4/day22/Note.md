## 凯伦闭包
1. ? -> if
2. * -> do ... while
3. + -> while
4. | -> switch

## SIGPIPE

```
int set = 1;
setsockopt(sd, SOL_SOCKET, SO_NOSIGPIPE, (void *)&set, sizeof(int));
```
