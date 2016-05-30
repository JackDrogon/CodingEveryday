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
	int fd = open("./fd_test_child", O_RDWR | O_CREAT);
	printf("parent: %d\n", fd);

	if (fork() == 0) {
		printf("child: %d\n", fd);
		write(fd, "child", 5);

		sleep(10);
	} else {
		close(fd);

		fd = open("./fd_test_parent", O_RDWR | O_CREAT);
		if (fd < 0) return 2;
		printf("parent: %d\n", fd);
		write(fd, "parent", 6);
		close(fd);

		sleep(10);
	}

	return 0;
}
