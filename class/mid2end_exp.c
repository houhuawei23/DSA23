/*读入一个中缀表达式，将其转换成后缀表达式*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char stack[100];

void mid2end(char *mid, char *end)
{
    char *p = mid;
    char *q = end;
    char *s = stack;
    char c;
    while (*p != '\0')
    {
        if (isnum(*p))
        {
            *q++ = *p++;
        }
        else
        {
            switch (*p)
            {
            case '(':
                *s++ = *p++;
                break;
            case ')':
                while (*(s - 1) != '(')
                {
                    *q++ = *--s;
                }
                s--;
                p++;
                break;
            case '+':
            case '-':
                while (s != stack && *(s - 1) != '(')
                {
                    *q++ = *--s;
                }
                *s++ = *p++;
                break;
            case '*':
            case '/':
                while (s != stack && *(s - 1) != '(' && *(s - 1) != '+' && *(s - 1) != '-')
                {
                    *q++ = *--s;
                }
                *s++ = *p++;
                break;
            default:
                break;
            }
        }
    }
    while (s != stack)
    {
        *q++ = *--s;
    }
    *q = '\0';
}

// isnum: 判断是否为数字
int isnum(char c)
{
    return c >= '0' && c <= '9';
}

// 测试
int main(){
    char mid[100];
    char end[100];
    printf("请输入中缀表达式：");
    scanf("%s", mid);
    mid2end(mid, end);
    printf("后缀表达式为：%s", end);
    return 0;
}