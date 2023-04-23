#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

Node *multiply(Node *num1, Node *num2);
Node *create_node(int data);
void insert_node(Node **head, int data);
void print_number(Node *head);
Node *power(int base, int exponent);
void count_digits(Node *head, int *count);

int main()
{
    int count[10] = {0};
    Node *result = power(2, 4000);
    count_digits(result, count);

    printf("The count of digits in 2^4000:\n");
    for (int i = 0; i < 10; i++)
    {
        printf("%d: %d\n", i, count[i]);
    }

    return 0;
}

Node *create_node(int data)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void insert_node(Node **head, int data)
{
    Node *new_node = create_node(data);
    new_node->next = *head;
    *head = new_node;
}

void print_number(Node *head)
{
    if (head == NULL)
        return;
    print_number(head->next);
    printf("%d", head->data);
}

Node *multiply(Node *num1, Node *num2)
{
    Node *result_head = NULL;
    Node *p1 = num1, *p2 = num2;
    int carry = 0;
    int product;
    int i, j;

    for (i = 0; p1 != NULL; i++)
    {
        p2 = num2;
        Node *temp_head = NULL;

        for (j = 0; j < i; j++)
        {
            insert_node(&temp_head, 0);
        }

        carry = 0;
        for (j = 0; p2 != NULL; j++)
        {
            product = p1->data * p2->data + carry;
            carry = product / 10;
            insert_node(&temp_head, product % 10);
            p2 = p2->next;
        }

        if (carry != 0)
        {
            insert_node(&temp_head, carry);
        }

        p1 = p1->next;

        Node *sum_head = NULL;
        Node *r = result_head, *t = temp_head;
        carry = 0;
        while (r != NULL || t != NULL)
        {
            int a = (r != NULL) ? r->data : 0;
            int b = (t != NULL) ? t->data : 0;
            int sum = a + b + carry;
            carry = sum / 10;
            insert_node(&sum_head, sum % 10);
            if (r != NULL)
                r = r->next;
            if (t != NULL)
                t = t->next;
        }

        if (carry != 0)
        {
            insert_node(&sum_head, carry);
        }

        result_head = sum_head;
    }

    return result_head;
}

Node *power(int base, int exponent)
{
    if (exponent == 0)
    {
        Node *one = create_node(1);
        return one;
    }
    else if (exponent == 1)
    {
        Node *base_node = create_node(base);
        return base_node;
    }
    else
    {
        Node *result = create_node(1);
        Node *base_node = create_node(base);
        for (int i = 0; i < exponent; i++)
        {
            Node *temp = multiply(result, base_node);
            result = temp;
        }
        return result;
    }
}

void count_digits(Node *head, int *count)
{
    Node *current = head;
    while (current != NULL)
    {
        count[current->data]++;
        current = current->next;
    }
}

// int main()
// {
//     int count[10] = {0};
//     Node *result = power(2, 4000);
//     count_digits(result, count);
//     printf("The count of digits in 2^4000:\n");
//     for (int i = 0; i < 10; i++)
//     {
//         printf("%d: %d\n", i, count[i]);
//     }

//     return 0;
// }