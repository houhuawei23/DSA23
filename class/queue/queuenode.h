#ifndef _NODE_H

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

struct queuenode
{
	struct queuenode *next; /*next为指向下一结点的指针*/
	ElementType data;
};
typedef struct queuenode Queuenode;

Queuenode* CreateQueue();
void In(Queuenode** rear, ElementType x);
ElementType Out(Queuenode** rear);

Queuenode* CreateQueue()
{
	Queuenode* rear = (Queuenode*)malloc(sizeof(Queuenode));
	rear->next = NULL;
	// rear->data = -9;
	return rear;
}

void In(Queuenode** rear, ElementType x)
{
	if((*rear)->next == NULL){
		(*rear)->data = x;
		(*rear)->next = *rear;
		return ;
	}
	Queuenode *p = (Queuenode*)malloc(sizeof(Queuenode));
	p->data = x;
	p->next = (*rear)->next;
	(*rear)->next = p;
	(*rear) = p;
}

ElementType Out(Queuenode** rear)
{
	ElementType result = (*rear)->next->data;
	if((*rear)->next == *rear){
		(*rear)->next = NULL;
		return result;
	}
	Queuenode* p = (*rear)->next;
	(*rear)->next = p->next;

	return result;
}
#endif