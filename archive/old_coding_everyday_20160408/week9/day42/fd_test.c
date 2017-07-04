// @doc 用来测试linux/unix 打开文件关闭后，再次打开fd是不是选择之前没有使用过得最小的字母
// 主要是用来验证redis的eventloop中开了一个定长数组，这样可以以fd下表来确定大小
// 感觉还是比Muduo的Map速度要快，当然这点消耗也是可以容忍的

#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	for (int i = 0; i < 13; ++i) {
		int fd = open("./fd_test.c", O_RDONLY);
		if (fd < 0) return 2;
		printf("%d\n", fd);
		close(fd);
	}
	
	return 0;
}
