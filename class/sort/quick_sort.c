// 快速排序

#include <stdio.h>
#include <stdlib.h>

/*
快速排序：
    1. 从数列中挑出一个元素，称为 “基准”（pivot）
    2. 重新排序数列，所有元素比基准值小的摆放在基准前面，所有元素比基准值大的摆放在基准后面
    3. 分别对基准前后的子数列重复 1、2步，直到每个子序列中只有一个元素为止
时间复杂度：
    最好情况：O(nlogn)
    最坏情况：O(n^2)
    平均情况：O(nlogn)
空间复杂度：O(logn)
稳定性：不稳定
*/
void quickSort(int *arr, int left, int right)
{
    int i, j, temp, pivot;
    if (left < right)
    {
        i = left;
        j = right;
        pivot = arr[left];
        while (i < j)
        {
            while (i < j && arr[j] >= pivot)
            {
                j--;
            }
            if (i < j)
            {
                arr[i++] = arr[j];
            }
            while (i < j && arr[i] <= pivot)
            {
                i++;
            }
            if (i < j)
            {
                arr[j--] = arr[i];
            }
        }
        arr[i] = pivot;
        quickSort(arr, left, i - 1);
        quickSort(arr, i + 1, right);
    }
}

int main(){
    int arr[] = {3, 1, 5, 7, 2, 4, 9, 6, 10, 8};
    int len = sizeof(arr) / sizeof(arr[0]);
    quickSort(arr, 0, len - 1);
    for (int i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}