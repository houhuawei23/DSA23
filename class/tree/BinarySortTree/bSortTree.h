#ifndef _BSORT_TREE_H_
#define _BSORT_TREE_H_

typedef struct btNode{
    int data;
    struct btNode *lchild;
    struct btNode *rchild;

}btNode, *btTree;




typedef struct bSortTree{
    btTree root;
    int size;
}bSortTree;



// void createTree()

void Init_btNode(btNode *node, int data);
void Insert_bSortTree(bSortTree *tree, int data);
void Create_bSortTree(bSortTree *tree, int *data, int size);

#endif
