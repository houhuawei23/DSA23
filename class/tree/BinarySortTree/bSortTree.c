#include <stdio.h>
#include <stdlib.h>

#include "bSortTree.h"

void Init_btNode(btNode *node, int data){
    node->data = data;
    node->lchild = NULL;
    node->rchild = NULL;
}

void Insert_bSortTree(bSortTree *tree, int data){
    btNode *node = (btNode *)malloc(sizeof(btNode));
    Init_btNode(node, data);
    if(tree->root == NULL){
        tree->root = node;
        return;
    }
    btNode *temp = tree->root;
    while(temp){
        if(data < temp->data){
            if(temp->lchild == NULL){
                temp->lchild = node;
                return;
            }
            temp = temp->lchild;
        }else{
            if(temp->rchild == NULL){
                temp->rchild = node;
                return;
            }
            temp = temp->rchild;
        }
    }
}
