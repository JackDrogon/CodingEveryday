#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct __list_node {
	void *value;
	__list_node *next;
} list_node;

typedef list_node *list_node_ptr;
typedef list_node *list;

list list_create()
{
	list l = (list) malloc(sizeof(list_node));
	if (l) {
		l->next = NULL;
		l->value = NULL;
	}

	return l;
}

void list_destory(list l)
{
	list_node_ptr p = l;
	while (l = l->next) {
		free(p);
		p = l;
	}
}

bool list_empty(list l)
{
	return l->next == NULL;
}

void list_push(list l, void *value)
{
	list_node_ptr ele = (list_node_ptr) malloc(sizeof(list_node));
	ele->next = NULL;    ele->value = value;
	while (l->next) {
		l = l-> next;
	}
	l->next = ele;
}



void list_
