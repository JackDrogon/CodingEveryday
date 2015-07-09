1. C语言不能在函数外进行赋值，但是可以声明和定义。
比如这样是可以的
```
struct __log_setting {
	char *logfile;
	uint8_t verbosity;
} log_setting = {.logfile = NULL, .verbosity = REDIS_DEBUG};
```
但是这样是不行的
```
struct __log_setting {
	char *logfile;
	uint8_t verbosity;
} log_setting 
log_setting = {.logfile = NULL, .verbosity = REDIS_DEBUG};
```
C99的strcut用法，可以对函数体的特定变量进行赋值和初始化
