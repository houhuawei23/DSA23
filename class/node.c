#include <node.h>

void InitNode(Node *Nod, int value, Node* ptr) {
    Nod->data = value;
    Nod->next = ptr;
}

void InsertAfter(Node*Nod, Node*ptr){
    ptr->next = Nod->next;
    Nod->next = ptr;
}
/*
返回指向被删除节点的指针
*/
Node* DeleteAfter(Node *p){
    Node *temp = p->next;
    if (temp == NULL) return NULL;
    p->next = temp->next;
    
    return temp;
}

/*创建单链表结点*/
Node* GetNode(int item, Node* nextptr){
    Node *temp = (Node*)malloc(sizeof(Node));

    if(temp == NULL){
        printf("内存分配失败！\n");
        exit(1);
    }
    InitNode(temp, item, nextptr);
    return temp;
}
/*释放节点*/
void FreeNode(Node *p){
    if (p == NULL){
        printf("节点为空！\n");
        return;
    }
    free(p);
}