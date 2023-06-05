// 单链表结点及操作方法的描述头文件node.h

#ifndef _NODE_H
#define _NODE_H
#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

typedef struct node Node;

void InitNode(Node *Nod, int value, Node* ptr); // 初始化结点
void InsertAfter(Node *Nod, Node* ptr); // 插入结点
Node* DeleteAfter(Node *p); // 删除结点
Node* GetNode(int item, Node *p); // 创建单链表结点
void FreeNode(Node *p); // 释放结点


#endif