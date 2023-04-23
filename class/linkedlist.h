/*定义单链表结构的类型说明及擦做方法*/

#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

enum boolean {FALSE, TRUE};
typedef enum boolean Bool;

struct linkedList{
    Node* front, *rear; // 表头指针和表尾指针
    Node *prevPtr, *currPtr;// 指向当前结点的前驱结点和当前结点的指针
    int size; // 链表的长度
    int position; // 当前结点的位置
};

typedef struct linkedList LinkedList;

// 申请节点空间

// 释放节点空间

// 初始化链表

// 判断是否为空链表

// 求当前结点的后继

// 求当前结点的前驱




#endif