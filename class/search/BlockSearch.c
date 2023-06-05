/* BlockSearch 分块查找 */

#include <stdio.h>
#include <stdlib.h>

/*
分块查找：  
    1. 将n个数据元素"按块有序"划分为m块（m ≤ n）。每一块中的结点不必有序，但块与块之间必须"按块有序"；
    2. 建立一个索引表，把每块中的最大关键字值按块的顺序存放在一个辅助数组中，称为索引表；
    3. 一个块的索引项需存有该块中的最大关键字、该块在数组中的起始位置以及该块的长度；
    4. 查找时先用给定的关键字值在索引表中查找，确定满足条件的数据元素可能存在的块，再在相应的块中顺序查找。
时间复杂度：O(logn)
空间复杂度：O(1)
*/

// 定义索引表结构
typedef struct
{
    int maxKey; // 每块中的最大关键字
    int begin;  // 每块在数组中的起始位置
    int length; // 每块的长度
} Index;

// 分块查找
int BlockSearch(int *arr, int len, Index *index, int indexLen, int key)
{
    int i, j;
    // 在索引表中查找
    for (i = 0; i < indexLen; i++)
    {
        if (key <= index[i].maxKey)
        {
            break;
        }
    }
    // 在对应块中顺序查找
    for (j = index[i].begin; j < index[i].begin + index[i].length; j++)
    {
        if (arr[j] == key)
        {
            return j;
        }
    }
    return -1;
}

int main()
{
    int arr[] = {1, 3, 5, 7, 9, 11, 13, 15};
    int len = sizeof(arr) / sizeof(int);
    int key = 11;
    Index index[] = {{5, 0, 3}, {11, 3, 3}, {15, 6, 2}};
    int indexLen = sizeof(index) / sizeof(Index);
    int index = BlockSearch(arr, len, index, indexLen, key);
    printf("index = %d\n", index);
    return 0;
}
