/*
stack.c - implementation of the stack functions
*/

#include "stack.h"

void InitStack(Stack *s, int size){// 初始化栈
    s->size = size;
    s->items = malloc(sizeof(int) * size);
    s->top = -1;
} 
void DestroyStack(Stack *s){
    free(s->items);
    s->size = 0;
    s->top = -1;
} // 销毁栈
void ClearStack(Stack *s){
    s->top = -1;
} // 清空栈
Bool StackEmpty(Stack *s){
    return s->top == -1;
} // 判断栈是否为空

Bool StackFull(Stack *s){
    return s->top == s->size - 1;
} // 判断栈是否为满

int StackLength(Stack *s){ // 求栈的长度
    return s->top + 1;
}
Bool GetTop(Stack *s, int *e){// 取栈顶元素
    if (s->top == -1) {
        return FALSE;
    }
    *e = s->items[s->top];
    return TRUE;
}

void Push(Stack *s, int e){ // 入栈
    if (s->top == s->size - 1) {
        printf("Error: Stack overflow.\n");
        return;
    }
    s->items[++s->top] = e;
}

Bool Pop(Stack *s, int *e){
    if (s->top == -1) {
        printf("Error: Stack underflow.\n");
        return FALSE;
    }
    *e = s->items[s->top--];
    return TRUE;
}

/*
*/
void StackTraverse(Stack *s, void (*visit)(int)){
    int i;
    for (i = 0; i <= s->top; i++) {
        visit(s->items[i]);
    }
    printf("\n");
}