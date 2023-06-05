/*实现kmp串匹配算法*/
/*
该kmp实现中的next[]数组是前后缀匹配数组右移一位后所得
则s[i]与p[j]不匹配时，回退到j = next[j]
其中特殊的是next[0] = -1，做特殊判断
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *GetNext(char *p)
{
    int *next = (int *)malloc(sizeof(int) * strlen(p));
    next[0] = -1;
    int i = 0;
    int j = -1;
    while (i < strlen(p) - 1)
    {
        if (j == -1 || p[i] == p[j])
        {
            i++;
            j++;
            next[i] = j;
        }
        else
        {
            j = next[j];
        }
    }
    for (int i = 0; i < strlen(p); i++)
    {
        printf("%c ", p[i]);
    }
    printf("\n");
    for (int i = 0; i < strlen(p); i++)
    {
        printf("%d ", next[i]);
    }
    printf("\n");
    return next;
}

int Kmp(char *s, char *p)
{
    int *next = GetNext(p);
    int i = 0;
    int j = 0;
    // i 是主串的下标
    // j 是模式串的下标
    while (i < strlen(s) && j < strlen(p))
    {
        // 如果j为-1，或者当前字符匹配成功（即S[i] == P[j]），都令i++，j++
        if (j == -1 || s[i] == p[j])
        {
            i++;
            j++;
        }
        else
        {
            // 如果j != -1，且当前字符匹配失败（即S[i] != P[j]），则令i不变，j = next[j]。
            // 此举意味着失配时，模式串P相对于主串S向右移动了j - next[j] 位
            j = next[j];
        }
    }
    if (j == strlen(p))
    {
        return i - j;
    }
    else
    {
        return -1;
    }
}

// 测试
int main()
{
    char s[] = "ababababca";
    char p[] = "abababca";
    // int *next = GetNext(p);
    // for(int i=0; i<strlen(p); i++){
    //     printf("%d ", next[i]);
    // }
    // printf("\n");
    int result = Kmp(s, p);
    printf("%d\n", result);
}