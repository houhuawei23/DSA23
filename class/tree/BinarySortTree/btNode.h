#ifndef _BTNODE_H_
#define _BTNODE_H_

typedef struct btNode
{
    int data;
    struct btNode *lchild;
    struct btNode *rchild;
}btNode, *btTree;




#endif