#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertAtEnd(Node** head, int data) {
    Node* newNode = createNode(data);
    if (!(*head)) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void multiply(Node** head, int num) {
    Node* temp = *head;
    int carry = 0;
    while (temp) {
        int product = temp->data * num + carry;
        temp->data = product % 10;
        carry = product / 10;
        if (!(temp->next) && carry) {
            insertAtEnd(head, carry);
            break;
        }
        temp = temp->next;
    }
}

void calculatePower(Node** head, int base, int exponent) {
    *head = createNode(1);
    for (int i = 0; i < exponent; ++i) {
        multiply(head, base);
    }
}

void countDigits(Node* head, int* count) {
    Node* temp = head;
    while (temp) {
        count[temp->data]++;
        temp = temp->next;
    }
}

int main() {
    int base = 2;
    int exponent = 4000;
    int count[10] = {0};
    Node* head = NULL;

    calculatePower(&head, base, exponent);
    countDigits(head, count);

    printf("2^%d的结果中0-9的个数分别为：\n", exponent);
    for (int i = 0; i < 10; ++i) {
        printf("%d: %d\n", i, count[i]);
    }

    return 0;
}
