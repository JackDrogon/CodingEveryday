#include <stdlib.h>
#include <stdio.h>
struct device {
	int num;
	int count;
	int reserve
	    [0]; // reserve是一个数组名；该数组没有元素；该数组的其实地址紧随结构device之后；这种声明方法可以巧妙的实现C语言里的数组扩展
};

int main()
{
	struct device *p_dev =
	    (struct device *)malloc(sizeof(struct device) + sizeof(int) * 25);
	// sizeof(int)*25是数组reserve的具体空间(25个元素)
	p_dev->reserve[0] = 100;
	p_dev->reserve[24] = 0;
	printf("p_dev->reserve[24] = %d\n", p_dev->reserve[24]);
	printf("sizeof(struct device) = %d\n", sizeof(struct device));

	// 将结构体device之后的第一个内容(int值，其实就是reserve[0]的值)赋值给变量a
	// int a = *((&(p_dev->count)) + 1);
	int a = *(&p_dev->count + 1);
	printf("a = %d\n", a);
}

// @doc Out
/*
 * p_dev->reserve[0] = 100
 * p_dev->reserve[24] = 0
 * sizeof(struct device) = 8
 * a = 100
 *
 * -------------------------------------------
 *
 * p_dev ---> |--------------|
 *            |int num       |
 *            |int count     |
 *            |--------------|      reserve是数组的名字;
 *    reserve |              |      由于数组没有元素，该数组在该结构体中分配占用空间
 *            |              |      所以sizeof(struct device) = 8
 *            |              |
 *            |              |
 *            |--------------|
 */
