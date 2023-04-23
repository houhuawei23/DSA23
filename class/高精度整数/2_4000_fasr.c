// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <math.h>

// typedef struct Node {
//     int data;
//     struct Node* next;
// } Node;

// Node* createNode(int data) {
//     Node* newNode = (Node*)malloc(sizeof(Node));
//     newNode->data = data;
//     newNode->next = NULL;
//     return newNode;
// }

// void insertAtBeginning(Node** head, int data) {
//     Node* newNode = createNode(data);
//     newNode->next = *head;
//     *head = newNode;
// }

// void multiply(Node** head, int num) {
//     Node* temp = *head;
//     int carry = 0;
//     while (temp) {
//         int product = temp->data * num + carry;
//         temp->data = product % 10;
//         carry = product / 10;
//         if (!(temp->next) && carry) {
//             insertAtBeginning(head, carry);
//             break;
//         }
//         temp = temp->next;
//     }
// }

// void fastPower(Node** head, int base, int exponent) {
//     *head = createNode(1);
//     while (exponent > 0) {
//         if (exponent % 2 == 1) {
//             multiply(head, base);
//         }
//         base *= base;
//         exponent /= 2;
//     }
// }

// void countDigits(Node* head, int* count) {
//     Node* temp = head;
//     while (temp) {
//         count[temp->data]++;
//         temp = temp->next;
//     }
// }

// int main() {
//     int base = 2;
//     int exponent = 4000;
//     int count[10] = {0};
//     Node* head = NULL;

//     fastPower(&head, base, exponent);
//     countDigits(head, count);

//     printf("2^%d的结果中0-9的个数分别为：\n", exponent);
//     for (int i = 0; i < 10; ++i) {
//         printf("%d: %d\n", i, count[i]);
//     }

//     return 0;
// }
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <math.h>

// #define MAX_SIZE 2000

// void multiply(int result[], int num) {
//     int carry = 0;
//     for (int i = 0; i < MAX_SIZE; ++i) {
//         int product = result[i] * num + carry;
//         result[i] = product % 10;
//         carry = product / 10;
//     }
// }

// void fastPower(int result[], int base, int exponent) {
//     result[0] = 1;
//     while (exponent > 0) {
//         if (exponent % 2 == 1) {
//             multiply(result, base);
//         }
//         base *= base;
//         exponent /= 2;
//     }
// }

// void countDigits(int result[], int count[]) {
//     for (int i = 0; i < MAX_SIZE; ++i) {
//         count[result[i]]++;
//     }
// }

// int main() {
//     int base = 2;
//     int exponent = 4000;
//     int result[MAX_SIZE] = {0};
//     int count[10] = {0};

//     fastPower(result, base, exponent);
//     countDigits(result, count);

//     printf("2^%d的结果中0-9的个数分别为：\n", exponent);
//     for (int i = 0; i < 10; ++i) {
//         printf("%d: %d\n", i, count[i]);
//     }

//     return 0;
// }
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *createNode(int data) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void append(Node *head, int data) {
    Node *newNode = createNode(data);
    Node *temp = head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newNode;
}

Node *multiply(Node *num1, Node *num2) {
    Node *result = createNode(0);
    Node *temp1 = num1;
    Node *temp2 = num2;
    int carry = 0;
    int product = 0;
    while (temp1) {
        int n1 = temp1->data;
        temp2 = num2;
        Node *res_temp = result;
        carry = 0;
        while (temp2) {
            int n2 = temp2->data;
            product = n1 * n2 + carry + res_temp->data;
            res_temp->data = product % 10;
            carry = product / 10;
            if (!res_temp->next && (carry || temp2->next)) {
                append(res_temp, 0);
            }
            res_temp = res_temp->next;
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
        if (!result->next && temp1) {
            append(result, 0);
        }
        result = result->next;
    }
    return result;
}

Node *quickPower(int base, int exponent) {
    Node *result = createNode(1);
    Node *baseNode = createNode(base);
    while (exponent) {
        if (exponent & 1) {
            result = multiply(result, baseNode);
        }
        baseNode = multiply(baseNode, baseNode);
        exponent >>= 1;
    }
    return result;
}

int main() {
    Node *result = quickPower(2, 4000);
    int count[10] = {0};
    Node *temp = result;
    while (temp) {
        count[temp->data]++;
        temp = temp->next;
    }
    for (int i = 0; i < 10; i++) {
        printf("数字%d出现的次数：%d\n", i, count[i]);
    }
    return 0;
}
