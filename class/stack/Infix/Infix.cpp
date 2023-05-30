/**********************************************************
    date: July 2017
    copyright: Zhu En（祝恩）
    DO NOT distribute this code.
**********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "LnkStack.h"
#include "Infix.h"

//////////////////////////////////////////////////////////////
void compute(LinkStack *so, LinkStack *sd)
//++++++++++++++++++++++++++++++++++++++++++++++
// so 运算符栈
// sd 操作数栈
// 1 从运算符栈出栈一个运算符
// 2 从操作数栈出栈两个操作数
// 3 用出栈的运算符对出栈的操作数进行运算
// 4 将运算结果进操作数栈
//+++++++++++++++++++++++++++++++++++++++++++++++
{
    T a, b, c, d;
    LS_Pop(so, c);
    LS_Pop(sd, a);
    LS_Pop(sd, b);
    if (c == '*')
        d = b * a;
    else if (c == '/')
        d = b / a;
    else if (c == '+')
        d = b + a;
    else if (c == '-')
        d = b - a;
    else
        printf("never occur!");
    LS_Push(sd, d);
}

double ComputeInfix(char *s)
// 计算中缀表达式
{
    // 请在此添加代码，补全函数ComputeInfix，计算中缀表达式
    /********** Begin *********/
    double res = 0;
    LinkStack *so = LS_Create();
    LinkStack *sd = LS_Create();
    int i = 0;
    while (s[i] != '\0')
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            LS_Push(sd, s[i] - '0');
        }
        else if (s[i] == '+' || s[i] == '-')
        {
            if (so->len == 0)
            {
                LS_Push(so, s[i]);
            }
            else
            {
                T c;
                LS_Top(so, c);
                if (c == '*' || c == '/')
                {
                    compute(so, sd);
                    LS_Push(so, s[i]);
                }
                else
                {
                    LS_Push(so, s[i]);
                }
            }
        }
        else if (s[i] == '*' || s[i] == '/')
        {
            if (so->len == 0)
            {
                LS_Push(so, s[i]);
            }
            else
            {
                T c;
                LS_Top(so, c);
                if (c == '*' || c == '/')
                {
                    compute(so, sd);
                    LS_Push(so, s[i]);
                }
                else
                {
                    LS_Push(so, s[i]);
                }
            }
        }
        else if (s[i] == '(')
        {
            LS_Push(so, s[i]);
        }
        else if (s[i] == ')')
        {
            T c;
            LS_Top(so, c);
            while (c != '(')
            {
                compute(so, sd);
                LS_Top(so, c);
            }
            LS_Pop(so, c);
        }

        i++;
    }

    while (so->len != 0)
    {
        compute(so, sd);
    }
    LS_Top(sd, res);

    return res;
    /********** End **********/
}
