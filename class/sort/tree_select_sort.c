// 树形选择排序/竞赛树排序/锦标赛排序

#include <stdio.h>
#include <stdlib.h>

/*
树形选择排序：
    1. 将待排序序列分成若干个子序列，每个子序列的元素个数为 1
    2. 将每个子序列进行直接选择排序
    3. 重复 1、2步，直到所有子序列中的元素个数大于 1
    4. 将上一步形成的子序列再次合并成一个有序序列
时间复杂度：
    最好情况：O(nlogn)
    最坏情况：O(nlogn)
    平均情况：O(nlogn)
空间复杂度：O(n)
稳定性：可使之稳定，当且仅当每次比较时，若两个元素相等，则选取序号较小的元素
*/
void treeSelectSort(int *arr, int len)
{
    int i, j, min, temp;
    for (i = len / 2 - 1; i >= 0; i--)
    {
        min = i;
        // 找到最小元素的下标 min
        for (j = 2 * i + 1; j < len; j = 2 * j + 1)
        {
            if (j + 1 < len && arr[j] < arr[j + 1])
            {
                j++;
            }
            if (arr[j] > arr[min])
            {
                min = j;
            }
        }
        // 交换
        if (min != i)
        {
            temp = arr[i];
            arr[i] = arr[min];
            arr[min] = temp;
        }
    }
    // 交换
    for (i = len - 1; i > 0; i--)
    {
        temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        min = 0;
        // 找到最小元素的下标 min
        for (j = 2 * min + 1; j < i; j = 2 * j + 1)
        {
            if (j + 1 < i && arr[j] < arr[j + 1])
            {
                j++;
            }
            if (arr[j] > arr[min])
            {
                min = j;
            }
        }
        // 交换
        if (min != 0)
        {
            temp = arr[0];
            arr[0] = arr[min];
            arr[min] = temp;
        }
    }
}