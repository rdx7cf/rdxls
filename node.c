#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "node.h"

Node* n_add(Node *root, void *value)
{
	Node *node, *temp_root = root;
	Node *n_create(void *);

	if((node = n_create(value)) == NULL)
	{
		return NULL;
	}

	if (temp_root != NULL)
	{
		while(temp_root->next != NULL)
			temp_root = temp_root->next;

		temp_root->next = node;
	}
		
	return node;
}

Node *n_create(void *value)
{
	Node *pn;

	if ((pn = (Node *) malloc(sizeof(Node))) != NULL)
	{
		pn->value = value;
	}
	else	
		fprintf(stderr, "rdxls: An error occurred while creating a node.\n");

	return pn;
}

int n_remove(Node *root, const void* value, int (*cmp)(const void *c1, const void *c2))
{
	Node *n_node, *p_node;

	for(
			Node *p_node = root, *n_node = root;
			n_node != NULL;
			p_node = p_node->next, n_node = p_node->next
	   )
	{
		if(cmp(n_node->value, value) == 0)
			break;
	}
	if(!n_node)
		return 1;

	p_node->next = n_node->next;
	free(n_node->value);
	free(n_node);
	
	return 0;
}

void n_applyToEach(Node *root, void (*func)(void *value))
{
	Node *temp_root = root;

	while(temp_root)
	{
		func(temp_root-gt);
		temp_root = temp_root->next;
	}
}
