// 直接选择排序

#include <stdio.h>
#include <stdlib.h>
/*
直接选择排序：
    1. 从待排序序列中，找到关键字最小的元素
    2. 如果最小元素不是待排序序列的第一个元素，将其和第一个元素互换
    3. 从余下的 N - 1 个元素中，找出关键字最小的元素，重复1、2步，直到排序结束

时间复杂度：
    最好情况：O(n^2)
    最坏情况：O(n^2)
    平均情况：O(n^2)
移动次数：O(n)
空间复杂度：O(1)
稳定性：不稳定
适用情况：
优点：
*/
void directSelectSort(int *arr, int len)
{
    int i, j, min, temp;
    for (i = 0; i < len - 1; i++)
    {
        min = i;
        // 找到最小元素的下标 min
        for (j = i + 1; j < len; j++)
        {
            if (arr[j] < arr[min])
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
}

// 测试
int main(){
    int arr[] = {1, 3, 2, 5, 4, 7, 6, 9, 8};
    int len = sizeof(arr) / sizeof(int);
    directSelectSort(arr, len);
    for (int i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    // system("pause");
    return 0;
}