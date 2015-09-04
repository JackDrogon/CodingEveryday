#include <stdio.h>
#include <stdlib.h>

typedef struct __vector {
	void **data;
	size_t length;
	size_t capacity;
} vector;

vector *vector_create()
{
	vector *vec = (vector *) malloc(sizeof(vector));
	if (vec) vec->length = vec->capacity = 0;

	return vec;
}

void vector_destory(vector *vec)
{
	for (size_t i = 0; i < vec->length; ++i) {
		if (vec->data[i]) free(vec->data[i]);
	}
	free(vec->data);
	vec->data = NULL;
	vec->length = vec->capacity = 0;
}

void *vector_nth(vector *vec, size_t place)
{
	if (place < vec->length) {
		return vec->data[place];
	} else {
		return NULL;
	}
}

void vector_replace(vector *vec, size_t place, void *val)
{
	if (place >= vec->length) {
		vec->data = (void **)realloc(vec->data, sizeof(void *) * place * 2);
		vec->length = place * 2;
	}
	vec->data[place] = val;
}

int main()
{
	
	return 0;
}
