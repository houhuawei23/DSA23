/*
stack.h栈的抽象数据类型的声明
*/

#ifndef _STACK_H_
#define _STACK_H_

enum boolean {FALSE, TRUE};
typedef enum boolean Bool;

struct stack{
    int top; // 栈顶指针
    int size; // 栈的大小
    int *items; // 存放栈元素的数组
};
typedef struct stack Stack;

void InitStack(Stack *s, int size); // 初始化栈
void DestroyStack(Stack *s); // 销毁栈
void ClearStack(Stack *s); // 清空栈
Bool StackEmpty(Stack *s); // 判断栈是否为
Bool StackFull(Stack *s); // 判断栈是否为满
int StackLength(Stack *s); // 求栈的长度
Bool GetTop(Stack *s, int *e); // 取栈顶元素
void Push(Stack *s, int e); // 入栈
Bool Pop(Stack *s, int *e); // 出栈
void StackTraverse(Stack *s, void (*visit)(int)); // 遍历栈

// 后缀表达式求值
int EvaluateExpression(char *exp);



#endif