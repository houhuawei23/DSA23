//
//  binary_tree.h

#ifndef __BTNODE_H
#define __BTNODE_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

typedef char ElemType;

typedef struct BTNode {
    ElemType data;          //  树节点元素
    BTNode* lchild;         //  左子树指针
    BTNode* rchild;         //  右子树指针
    BTNode() {              //  树节点初始化
        lchild = NULL;
        rchild = NULL;
    }
    BTNode(ElemType item) { //  用元素初始化树节点
        data = item;
        lchild = NULL;
        rchild = NULL;
    }
    ~BTNode() {             //  释放树节点内存
        lchild = NULL;
        rchild = NULL;
    }
} BTNode;

//创建新结点的工具函数
BTNode* getNewNode(ElemType e);

// 利用二叉树的括号表示法创建二叉树root
// 参数：二叉树的根结点指针root。
// 参数：二叉树的括号表示法字符串s。
void CreateTree(BTNode* &root, ElemType* s);

//以嵌套括号表示法输出一棵树
void DispTree(BTNode* root);

// 求二叉树的高度
// 参数：二叉树根节点root
int getHeight(BTNode* root);

#endif /* __BTNODE_H */
 