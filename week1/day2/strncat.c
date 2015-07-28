#include <stdlib.h>

char *strncat(char *restrict dest, const char *restrict src, size_t n)
{
	char *origin = dest;
	dest += strlen(dest);

	while (n-- && *src) *dest++ = *src++;
	*dest++ = '\0';

	return dest;
}

// 下面这点写法效率会比较低
// char* strncat(char *dest, const char *src, size_t n)
// {
// 	size_t dest_len = strlen(dest);
// 	size_t i;
// 
// 	for (i = 0 ; i < n && src[i] != '\0' ; i++)
// 	dest[dest_len + i] = src[i];
// 	dest[dest_len + i] = '\0';
// 
// 	return dest;
// }
