#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
/********** Begin **********/
// 定义全局变量，结构体，函数等 
// 循环链表结构体
typedef struct Node{
    int index;
    Node *pre;
    Node *next;
}Node;

Node* build_list(int n){
    Node *head = new Node;
    head->index = 1;
    head->pre = head;
    head->next = head;
    Node *p = head;
    for(int i = 2; i <= n; i++){
        Node *q = new Node;
        q->index = i;
        q->pre = p;
        q->next = head;
        p->next = q;
        head->pre = q;
        p = q;
    }
    return head;
}

void delete_node(Node *p){
    p->pre->next = p->next;
    p->next->pre = p->pre;
    delete p;
}





/********** End **********/

int main(){
	/********** Begin **********/
    // 约瑟夫问题
    int n, k;
    cin >> n >> k;
    Node *head = build_list(n);
    Node *p = head;
    while(p->next != p){
        for(int i = 1; i < k; i++){
            p = p->next;
        }
        Node *q = p->next;
        // cout << q->index << " ";
        delete_node(q);
        p = p->next;
    }
    // cout << "final: "<< p->index << endl;
    cout<< p->index<<endl;
	/********** End **********/
	
	return  0;
} 