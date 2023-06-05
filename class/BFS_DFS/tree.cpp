#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
/********** Begin **********/
// 定义全局变量，结构体，函数等
typedef struct Node
{
    int v;
    Node *left, *right;
    Node() : v(0), left(NULL), right(NULL) {}
    Node(int v) : v(v), left(NULL), right(NULL) {}
} Node;

Node *root = NULL;
bool failed = true;
int all = 0;
int cnt = 0;
int buf[1000];
int i=0;
Node * newnode(int v = 0){
    return new Node(v);
}

void remove_tree(Node* root){
    if(root == NULL) return;
    remove_tree(root->left);
    remove_tree(root->right);
    delete root;
}

void addnode(int v, char *s)
{
    int n = strlen(s);
    Node *u = root;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == 'L')
        {
            if (u->left == NULL){
                u->left = new Node();
                all ++;
            }
            u = u->left;
        }
        else if (s[i] == 'R')
        {
            if (u->right == NULL){
                u->right = new Node();
                all ++;
            }
            u = u->right;
        }
    }
    if (u->v != 0){
        failed = true;
        return;
    }
    u->v = v;
    cnt++;
}

void hierarchy_traverse(Node *root)
{
    if (root == NULL)
        return;
    queue<Node *> q;
    q.push(root);
    int count = 1;
    while (!q.empty())
    {
        Node *u = q.front();
        q.pop();
        printf("%d", u->v);
        count--;
        if (u->left != NULL){
            q.push(u->left);
            count++;
        }
        if (u->right != NULL){
            q.push(u->right);
            count++;
        }
        if(count > 0){
            printf(" ");
        }
        
    }
}
/********** End **********/
char s[500];
bool input()
{
    failed = false;
    while (true)
    {
        if (scanf("%s", s) != 1)
            return false;
        if (!strcmp(s, "()"))
            break; // 两个字符穿相同对于零
        int v;
        sscanf(&s[1], "%d", &v);
        addnode(v, strchr(s, ',') + 1);
    }
    return true;
}
int main()
{
    while (true)
    {
        remove_tree(root);
        root = newnode();
        all = 0;
        cnt=0;
        i=0;
        bool a = input();
        if (!a)
            break;
        /********** Begin **********/
        // 层次遍历
        
        if(failed || all != cnt - 1 ){
            printf("-1\n");
        }
        else{
            hierarchy_traverse(root);
            printf("\n");
        }
        /********** End **********/
    }
    return 0;
}