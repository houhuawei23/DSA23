/*
用链表构造高精度整数，实现2^4000的计算
res:
0: 126
1: 112
2: 127
3: 109
4: 129
5: 115
6: 129
7: 124
8: 125
9: 109
*/
#include <stdio.h>
#include <stdlib.h>

// 定义链表节点结构体
typedef struct node {
    int val;            // 节点存储的数字
    struct node* next;  // 指向下一个节点的指针
} ListNode;

// 用链表表示一个大整数
ListNode* createList() {
    ListNode* head = (ListNode*)malloc(sizeof(ListNode));
    head->val = 1;  // 初始化为1
    head->next = NULL;
    return head;
}

// 大整数乘以2，返回乘积的最高位
int multiplyBy2(ListNode* head) {
    int carry = 0;  // 进位
    ListNode* p = head;
    while (p != NULL) {
        int newVal = p->val * 2 + carry;
        carry = newVal / 10;  // 计算进位
        p->val = newVal % 10; // 计算当前位的值
        p = p->next;
    }
    if (carry != 0) {  // 如果最高位有进位，则需要新增一个节点
        ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
        newNode->val = carry;
        newNode->next = NULL;
        p = head;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = newNode;
    }
    return head->val;
}

// 统计数字出现次数
void countDigits(ListNode* head, int* count) {
    ListNode* p = head;
    while (p != NULL) {
        count[p->val]++;
        p = p->next;
    }
}

int main() {
    int count[10] = {0};  // 初始化每个数字出现次数为0
    ListNode* head = createList();
    for (int i = 0; i < 4000; i++) {
        multiplyBy2(head);
    }
    countDigits(head, count);
    printf("0: %d\n", count[0]);
    printf("1: %d\n", count[1]);
    printf("2: %d\n", count[2]);
    printf("3: %d\n", count[3]);
    printf("4: %d\n", count[4]);
    printf("5: %d\n", count[5]);
    printf("6: %d\n", count[6]);
    printf("7: %d\n", count[7]);
    printf("8: %d\n", count[8]);
    printf("9: %d\n", count[9]);
    return 0;
}
