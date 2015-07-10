#include <stdlib.h>

char *strncat(char *restrict dest, const char *restrict src, size_t n)
{
	char *origin = dest;
	dest += strlen(dest);

	while (n-- && *src) *dest++ = *src++;
	*dest++ = '\0';

	return dest;
}
