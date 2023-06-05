// #pragma execution_character_set("utf-8")

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define TABLE_SIZE 256

int *build_bad_table(const char *pattern);
int *build_good_table(const char *pattern);
bool is_prefix(const char *pattern, int p);
int suffix_length(const char *pattern, int p);

int pattern(const char *pattern, const char *target)
{
    int tLen = strlen(target);
    int pLen = strlen(pattern);

    if (pLen > tLen)
    {
        return -1;
    }

    int *bad_table = build_bad_table(pattern);
    int *good_table = build_good_table(pattern);
    printf("bad_table: \n");
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        printf("%d ", bad_table[i]);
    }
    printf("\n");
    printf("good_table: \n");
    for(int i = 0; i < pLen; i++)
    {
        printf("%d ", good_table[i]);
    }
    printf("\n");
    // i 指向主串，j 指向模式串
    for (int i = pLen - 1, j; i < tLen;)
    {
        for (j = pLen - 1; target[i] == pattern[j]; i--, j--)
        {
            // 只要当前i，j所指的字符匹配，就继续比较下一个字符（向左）
            // 若 j == 0，意味着模式串已经比到头了，说明整串匹配成功，返回
            if (j == 0)
            {
                free(bad_table);
                free(good_table);
                return i;
            }
        }
        // 未成功整串匹配，此时有 target[i] != pattern[j] 
        // 如果出现坏字符，那么这个时候比较坏字符以及好后缀的数组，哪个大用哪个
        i += fmax(good_table[pLen - j - 1], bad_table[(unsigned char)target[i]]);
    }
    free(bad_table);
    free(good_table);
    return -1;
}

int *build_bad_table(const char *pattern)
{
    int *bad_table = (int *)malloc(TABLE_SIZE * sizeof(int));
    int pLen = strlen(pattern);
    // bad_table 数组 初始化为 pLen
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        bad_table[i] = pLen;
    }
    // 以字符的 ASCII 码值为下标，记录字符最后（右）出现的位置（下标）
    for (int i = 0; i < pLen - 1; i++)
    {
        int k = (unsigned char)pattern[i];
        bad_table[k] = pLen - 1 - i;
    }
    return bad_table;
}

int *build_good_table(const char *pattern)
{
    int pLen = strlen(pattern);
    int *good_table = (int *)malloc(pLen * sizeof(int));
    // 记录最新前缀的相对位置，初始化为模式串长度
    // pattern最长相等前后缀时，最长后缀的位置 lastPrefixPosition
    int lastPrefixPosition = pLen;

    for (int i = pLen - 1; i >= 0; --i)
    {
        if (is_prefix(pattern, i + 1))
        {
            // 如果 pattern[i + 1: pLen] == pattern[0: pLen - i - 1]
            // 即 pattern i 位置之后的子串是 pattern 的前缀（不包括i）
            lastPrefixPosition = i + 1;
        }
        // j = pLen - 1 - i
        good_table[pLen - 1 - i] = lastPrefixPosition - i + pLen - 1;
    }
    printf("good_table1: \n");
    for(int i = 0; i < pLen; i++)
    {
        printf("%d ", good_table[i]);
    }
    printf("\n");
    for (int i = 0; i < pLen - 1; ++i)
    {
        int slen = suffix_length(pattern, i);
        good_table[slen] = pLen - 1 - i + slen;
    }
    printf("good_table2: \n");
    for(int i = 0; i < pLen; i++)
    {
        printf("%d ", good_table[i]);
    }
    printf("\n");
    return good_table;
}
/*
前缀匹配
判断模式串 pattern 的 p 位置开始的子串是否为前缀
即判断 pattern[p: pLen] =?= pattern[0: pLen-p]
*/
bool is_prefix(const char *pattern, int p)
{
    int pLen = strlen(pattern);

    for (int i = p, j = 0; i < pLen; ++i, ++j)
    {
        if (pattern[i] != pattern[j])
        {
            return false;
        }
    }
    return true;
}
/*
后缀匹配
查找 pattern[0: p] 与 pattern[0: pLen - 1] 的最长公共后缀子串的长度
*/
int suffix_length(const char *pattern, int p)
{
    int pLen = strlen(pattern);
    int len = 0;

    for (int i = p, j = pLen - 1; i >= 0 && pattern[i] == pattern[j]; i--, j--)
    {
        len += 1;
    }
    return len;
}

int main()
{
    const char *p = "example";
    const char *t = "this is an example text for bm algorithm";

    int result = pattern(p, t);

    if (result != -1)
    {
        printf("success, match at position %d\n", result);
    }
    else
    {
        printf("failed\n");
    }

    return 0;
}
