#include <stdio.h>
#include <stdint.h>

union __byte_order {
	uint16_t lvalue;
	uint8_t svalue[2];
} order;

int main()
{
	order.lvalue = 0x0102;
	if (order.svalue[0] == 0x01) {
		printf("This machine is big endian!\n");
	} else {
		printf("This machine is little endian!\n");
	}

	return 0;
}
