// 冒泡排序

#include <stdio.h>
#include <stdlib.h>

/*
冒泡排序：
    1. 比较相邻的元素，如果第一个比第二个大，就交换他们两个
    2. 对每一对相邻元素做同样的工作，从开始第一对到结尾的最后一对，这样最后的元素应该会是最大的数
    3. 针对所有的元素重复以上的步骤，除了最后一个
    4. 重复 1~3，直到排序完成
时间复杂度：
    最好情况：O(n)
    最坏情况：O(n^2)
    平均情况：O(n^2)
空间复杂度：O(1)
稳定性：稳定
*/
int cnt = 0;
void bubbleSort(int *arr, int len)
{
    int i, j, temp;
    int not_change = 1; // 用于优化，如果一趟下来没有发生交换，说明已经有序，直接退出
    for (i = 0; i < len - 1; i++)
    {
        not_change = 1;
        for (j = 0; j < len - 1 - i; j++)
        {
            cnt++;
            if (arr[j] > arr[j + 1])
            {
                // 交换
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                not_change = 0;
            }
        }
        if (not_change)
            break;
    }
}

// 测试
int main()
{
    // int arr[] = {3, 1, 5, 7, 2, 4, 9, 6, 10, 8};
    int arr[] = {1, 2,3,4,5,6,7};
    // int arr[] = {7,6,5,4,3,2,1}; 
    int len = sizeof(arr) / sizeof(arr[0]);
    bubbleSort(arr, len);
    for (int i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("cnt: %d\n",cnt);
    // system("pause");
    return 0;
}
