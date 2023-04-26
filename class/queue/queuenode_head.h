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
// rear->data存放链表长度，rear作为附加尾结点
Queuenode* CreateQueue()
{
	Queuenode* rear = (Queuenode*)malloc(sizeof(Queuenode));
	rear->next = NULL;
	rear->data = 0;
	return rear;
}

void In(Queuenode** rear, ElementType x)
{
	Queuenode *p = (Queuenode*)malloc(sizeof(Queuenode));
	p->data = (*rear)->data + 1;
	(*rear)->data = x;
	p->next = (*rear)->next;
	(*rear)->next = p;
	(*rear) = p;
}

ElementType Out(Queuenode** rear)
{
	Queuenode *head = (*rear)->next;
	ElementType x = head->data;
	if(head->next == (*rear)){
		(*rear)->next = NULL;
		(*rear)->data = 0;
	}
	(*rear)->next = head->next;
	(*rear)->data --;
	free(head);
	return x;
}
#endif