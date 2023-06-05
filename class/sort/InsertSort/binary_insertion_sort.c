// 折半插入排序

#include <stdio.h>
#include <stdlib.h>

/*
折半排序算法
    1. 从第一个元素开始，该元素可以认为已经被排序
    2. 取出下一个元素，在已经排序的元素序列中折半查找到第一个大于该元素的位置
    3. 将新元素插入到该位置后
    4. 重复步骤2~3
时间复杂度：（比较 + 移动）
    最好情况：O(nlogn)
    最坏情况：O(n^2)
    平均情况：O(n^2)
比较次数：O(nlogn)
移动次数：worst O(n^2) best O(n)
空间复杂度：O(1)
稳定性：稳定
*/

void BinaryInsertionSort(int *arr, int len)
{
    int i, j, temp, low, high, mid;
    // 遍历待排序数组
    for (i = 1; i < len; i++)
    {
        temp = arr[i];
        low = 0;
        high = i - 1;
        while (low <= high) // 折半查找
        {
            // high < low 时结束折半查找
            mid = (low + high) / 2;
            if (arr[mid] > temp)
            {
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
        // 移动元素
        for (j = i - 1; j >= high + 1; j--)
        {
            arr[j + 1] = arr[j];
        }
        arr[high + 1] = temp;
    }
}

// 测试
int main(){
    int arr[] = {1, 3, 2, 5, 4, 7, 6, 9, 8};
    int len = sizeof(arr) / sizeof(int);
    BinaryInsertionSort(arr, len);
    for (int i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    return 0;
}