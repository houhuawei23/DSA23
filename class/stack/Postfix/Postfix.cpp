/**********************************************************
	date: July 2017
    copyright: Zhu En
    DO NOT distribute this code.
**********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "LnkStack.h"
#include "Postfix.h"
double ComputePostfix(char* s)
{
    // 请在此添加代码，补全函数ComputePostfix，计算后缀表达式
    /********** Begin *********/
    double res = 0;
    LinkStack *sd = LS_Create();
    int i = 0;
    while(s[i]!= '\0'){
        if(s[i] >= '0' && s[i] <= '9'){
            LS_Push(sd, s[i] - '0');
        }
        else if(s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/'){
            double a, b, c;
            LS_Pop(sd, a);
            LS_Pop(sd, b);
            if(s[i] == '+')
                c = b + a;
            else if(s[i] == '-')
                c = b - a;
            else if(s[i] == '*')
                c = b * a;
            else if(s[i] == '/')
                c = b / a;
            LS_Push(sd, c);
        }
        i++;
    }
    LS_Pop(sd, res);
    return res;
    /********** End **********/
}