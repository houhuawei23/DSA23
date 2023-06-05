// 直接插入排序

#include <stdio.h>
#include <stdlib.h>
/*
直接排序算法
    1. 从第一个元素开始，该元素可以认为已经被排序
    2. 取出下一个元素，在已经排序的元素序列中从后向前扫描
    3. 如果该元素（已排序）大于新元素，将该元素移到下一位置
    4. 重复步骤3，直到找到已排序的元素小于或者等于新元素的位置
    5. 将新元素插入到该位置后
    6. 重复步骤2~5
时间复杂度：
    最好情况：O(n): 有序
    最坏情况：O(n^2): 逆序
    平均情况：O(n^2): 无序
空间复杂度：O(1)
稳定性：稳定

适用情况：
*/
void directInsertionSort(int *arr, int len)
{
    int i, j, temp;
    for (i = 1; i < len; i++)
    {
        temp = arr[i];
        for (j = i - 1; j >= 0 && arr[j] > temp; j--)
        {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = temp;
    }
}

void directInsertionSort2(int* arr, int len){
    int i;
    for(i = 1; i < len; i++){
        int temp = arr[i];
        int j = i - 1;
        while(j >= 0 && arr[j] > temp){
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

// use memmove to move elements
// void direcInsertionSort3(int* arr, int len){
//     int j;
//     void *saved = malloc(sizeof(int));
//     for(j =1; j < len; j++){
//         int i = j- 1;
//         void* value = base + j * 
//     }
// }

// 测试

int main(){
    int arr[] = {20, 3, 2, 5, 4, 7, 6, 9, 8};
    int len = sizeof(arr) / sizeof(int);
    directInsertionSort2(arr, len);
    for (int i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    // system("pause");
    return 0;
}