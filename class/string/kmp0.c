/*
该kmp算法实现的next[i]数组为0~i串的最长公共前后缀
则s[i]与p[j]不匹配时，回退到j = next[j-1]
*/
#include <stdio.h>
#include <string.h>

// next[j] 记录着0~j子串的最长公共前后缀长度
void getNext(int *next, const char *s)
{
    // init j 是前缀末尾的下标
    int j = 0;
    next[0] = 0;
    // i 遍历模式串s，i是后缀的末尾下标
    for (int i = 1; i < strlen(s); i++)
    {
        // 前缀尾与后缀尾不匹配，继续向前回溯，回退到相同前后缀的后一位
        while (j > 0 && s[i] != s[j])
        {
            // 连续回退，直到找到一个相同的前后缀
            // 或者回退到0，即没有相同的前后缀，j = next[0] = 0
            j = next[j - 1];
        }
        // 前缀尾与后缀尾匹配，前缀长度+1
        if (s[i] == s[j])
        {
            j++;
        }
        // 记录当前i的最长公共前后缀长度
        next[i] = j;
    }
    for(int i = 0; i < strlen(s); i++)
    {
        printf("%d ", next[i]);
    }
    printf("\n");
}
// kmp 返回模式串p在主串s中的位置
int kmp(const char *s, const char *p)
{
    int next[strlen(p)];
    getNext(next, p);
    // i 遍历主串s，j 遍历模式串p
    int j = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        // 前缀尾与后缀尾不匹配，继续向前回溯
        while (j > 0 && s[i] != p[j])
        {
            j = next[j - 1];
        }
        // 前缀尾与后缀尾匹配，前缀长度+1
        if (s[i] == p[j])
        {
            j++;
        }
        // 找到匹配的模式串
        if (j == strlen(p))
        {
            return i - j + 1;
        }
    }
    return -1;
}

int main()
{
    char s[] = "ababababca";
    char p[] = "abababca";
    printf("%d\n", kmp(s, p));
    return 0;
}