#ifndef _NODE_H_
#define _NODE_H_

#define BUFSZ	1024

typedef struct node
{
	struct node *next;
	void*  value;
} Node;

Node* n_add(Node *, void *); // If the first parameter is NULL, a node is created; 
			     // otherwise, a new node with the given value is appended to the end of the linked list.
int n_remove(Node *, const void *, int (*)(const void *, const void *));
void n_applyToEach(Node *, void (*)(void *));

#endif
