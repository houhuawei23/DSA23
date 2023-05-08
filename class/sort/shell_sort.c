// shell排序法/缩小增量排序法

#include <stdio.h>
#include <stdlib.h>

/*
shell排序法：
    利用了直接插入排序的特点，先使数组基本有序，再进行直接插入排序。    
    1. 选择一个增量序列t1，t2，…，tk，其中ti>tj，tk=1；
    2. 按增量序列个数k，对序列进行k 趟排序；
    3. 每趟排序，根据对应的增量ti，将待排序列分割成若干长度为m 的子序列，
       分别对各子表进行直接插入排序。仅增量因子为1 时，整个序列作为一个表来处理，
       表长度即为整个序列的长度。
时间复杂度：
    最好情况：O(nlogn)
    最坏情况：O(n^2)
    平均情况：O(n^1.3)
比较次数：O(nlogn)
空间复杂度：O(1)
稳定性：不稳定
适用情况：n较大，无序，记录数较多
*/
void shellSort(int *arr, int len)
{
    int i, j, temp, gap;
    // gap为步长，每次减为原来的一半。
    for (gap = len / 2; gap > 0; gap /= 2)
    {
        // 共gap个组，对每一组都执行直接插入排序
        for (i = 0; i < gap; i++)
        {
            for (j = i + gap; j < len; j += gap)
            {
                // 如果a[j] < a[j-gap]，则寻找a[j]位置，并将后面数据的位置都后移。
                if (arr[j] < arr[j - gap])
                {
                    temp = arr[j];
                    int k = j - gap;
                    while (k >= 0 && arr[k] > temp)
                    {
                        arr[k + gap] = arr[k];
                        k -= gap;
                    }
                    arr[k + gap] = temp;
                }
            }
        }
    }
}

// 测试
int main()
{
    int arr[] = {1, 3, 2, 5, 4, 7, 6, 9, 8};
    int len = sizeof(arr) / sizeof(int);
    shellSort(arr, len);
    for (int i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    return 0;
}