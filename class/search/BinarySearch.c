/* BinarySearch */

#include <stdio.h>
#include <stdlib.h>

/*
折半查找：
    1. 从有序数组的中间元素开始查找，如果该元素正好是目标元素，则查找成功
    2. 如果目标元素大于或者小于中间元素，则在数组大于或小于中间元素的那一半中查找，然后重复第一步的操作
    3. 如果某一步数组为空，则表示找不到目标元素
时间复杂度：O(logn)
空间复杂度：O(1)
*/
int BinarySearch(int *arr, int len, int key)
{
    int low = 0;
    int high = len - 1;
    int mid;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (arr[mid] == key)
        {
            return mid;
        }
        else if (arr[mid] > key)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
}

int main(){
    int arr[] = {1, 3, 5, 7, 9, 11, 13, 15};
    int len = sizeof(arr) / sizeof(int);
    int key = 11;
    int index = BinarySearch(arr, len, key);
    printf("index = %d\n", index);
    return 0;
}