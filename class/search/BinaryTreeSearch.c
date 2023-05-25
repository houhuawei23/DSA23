/* 二叉查找树 */
#include <stdio.h>
#include <stdlib.h>

/*
二叉查找树：
    1. 左子树上所有结点的值均小于或等于它的根结点的值
    2. 右子树上所有结点的值均大于或等于它的根结点的值
    3. 左、右子树也分别为二叉排序树
时间复杂度：
    最好情况：O(logn)
    最坏情况：O(n)
    平均情况：O(logn)
空间复杂度：O(1)
*/

// 定义二叉树结点
typedef struct BSTNode
{
    int data;
    struct BSTNode *lchild;
    struct BSTNode *rchild;
} BSTNode;

// 查找
BSTNode *BSTSearch(BSTNode *root, int key)
{
    if (root == NULL)
    {
        return NULL;
    }
    if (root->data == key)
    {
        return root;
    }
    else if (root->data > key)
    {
        return BSTSearch(root->lchild, key);
    }
    else
    {
        return BSTSearch(root->rchild, key);
    }
}

// 插入
void BSTInsert(BSTNode **root, int key)
{
    if (*root == NULL)
    {
        *root = (BSTNode *)malloc(sizeof(BSTNode));
        (*root)->data = key;
        (*root)->lchild = NULL;
        (*root)->rchild = NULL;
    }
    else if ((*root)->data > key)
    {
        BSTInsert(&(*root)->lchild, key);
    }
    else
    {
        BSTInsert(&(*root)->rchild, key);
    }
}
// 删除
void BSTDelete(BSTNode **root, int key)
{
    if (*root == NULL)
    {
        return;
    }
    else
    {
        if ((*root)->data == key)
        {
            BSTNode *temp;
            if ((*root)->lchild == NULL)
            {
                temp = *root;
                *root = (*root)->rchild;
                free(temp);
            }
            else if ((*root)->rchild == NULL)
            {
                temp = *root;
                *root = (*root)->lchild;
                free(temp);
            }
            else
            {
                temp = (*root)->rchild;
                while (temp->lchild != NULL)
                {
                    temp = temp->lchild;
                }
                (*root)->data = temp->data;
                BSTDelete(&(*root)->rchild, temp->data);
            }
        }
        else if ((*root)->data > key)
        {
            BSTDelete(&(*root)->lchild, key);
        }
        else
        {
            BSTDelete(&(*root)->rchild, key);
        }
    }
}

// 创建二叉查找树
void createBST(BSTNode **root, int *arr, int len)
{
    int i;
    for (i = 0; i < len; i++)
    {
        BSTInsert(root, arr[i]);
    }
}

// 中序遍历
void inOrder(BSTNode *root)
{
    if (root == NULL)
    {
        return;
    }
    inOrder(root->lchild);
    printf("%d ", root->data);
    inOrder(root->rchild);
}
// 中序遍历，打印树形结构
// void inOrderPrint(BSTNode *root){

// }

void printBSTree(BSTNode *root, int depth, char flag) {

    if (root == NULL) {
        return;
    }
    int i;
    for (i = 0; i < depth; i++) {
        printf("    ");
    }
    if (flag == 'l') {
        printf("%d", root->data);
    } else if (flag == 'r') {
        printf("%d", root->data);
    } else {
        printf("%d", root->data);
    }
    printf("\n");
    printBSTree(root->lchild, depth + 1, 'l');
    printBSTree(root->rchild, depth + 1, 'r');
}




// 测试
int main(){
    int arr[] = {5, 3, 7, 1, 4, 6, 8};
    int len = sizeof(arr) / sizeof(int);
    BSTNode *root = NULL;
    createBST(&root, arr, len);
    inOrder(root);
    printf("\n");
    printBSTree(root, 0, 'n');
    printf("\n");
    BSTNode *node = BSTSearch(root, 7);
    printf("node->data = %d\n", node->data);
    BSTDelete(&root, 7);
    inOrder(root);
    printf("\n");
    // BSTNode *node2 = BSTSearch(root, 7);
    return 0;
}