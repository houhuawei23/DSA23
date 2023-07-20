#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <stdlib.h>

// 交换数组中两个元素的位置
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 寻找数组中第k小的元素
int findKthSmallest(int* arr, int left, int right, int k) {
#ifdef DEBUG
    printf("findKthSmallest: left = %d, right = %d, k = %d\n", left, right, k);
#endif // DEBUG
    if (left == right) // 如果数组只有一个元素，直接返回该元素
        return arr[left];

    // 如果数组大小小于等于5，使用插入排序
    if (right - left + 1 <= 5) {
        for (int i = left + 1; i <= right; i++) {
            int key = arr[i];
            int j = i - 1;
            while (j >= left && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
        return arr[left + k - 1];
    }

    // 划分为五个元素一组，并找到各组的中位数
    int numGroups = (right - left + 1) / 5;
    int i;
    for (i = 0; i < numGroups; i++) {
        int groupLeft = left + i * 5;
        int groupRight = groupLeft + 4;
        int median = findKthSmallest(arr, groupLeft, groupRight, 2); // 找到当前组的中位数
        swap(&arr[left + i], &arr[median]);
    }

    int lastGroupSize = (right - left + 1) % 5;
    if (lastGroupSize > 0) {
        int lastGroupLeft = left + numGroups * 5;
        int lastGroupRight = lastGroupLeft + lastGroupSize - 1;
        int median = findKthSmallest(arr, lastGroupLeft, lastGroupRight, (lastGroupSize + 1) / 2);
        swap(&arr[left + numGroups], &arr[median]);
        numGroups++;
    }

    // 递归地寻找中位数的中位数（中位数的下标为numGroups / 2）
    int mid = (numGroups + 4) / 5;
    if (mid == 0) {
        return arr[left + numGroups / 2];
    }
    else {
        return findKthSmallest(arr, left, left + numGroups - 1, mid);
    }
#ifdef DEBUG
    printf("end: findKthSmallest: left = %d, right = %d, k = %d\n", left, right, k);
#endif // DEBUG
}

// 获取数组的中值
int get_med(int* arr, int len) {
#ifdef DEBUG
    printf("get_med: len = %d\n", len);
#endif // DEBUG
    if (arr == NULL || len <= 0)
        return -1;

    int medianIndex = (len + 1) / 2;
    int median = findKthSmallest(arr, 0, len - 1, medianIndex);
    return median;
}

// 快速排序的分割函数
int partition(int* arr, int low, int high) {
    int pivot = arr[high]; // 选择最后一个元素作为枢轴
    int i = low - 1; // i 指向小于枢轴的元素的位置

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]); // 将小于枢轴的元素放到前面
        }
    }
    swap(&arr[i + 1], &arr[high]); // 将枢轴放到正确的位置上
    return i + 1; // 返回枢轴的位置
}

// 快速排序算法
void quickSort(int* arr, int low, int high) {
#ifdef DEBUG
    printf("quickSort: low = %d, high = %d\n", low, high);
#endif // DEBUG
    if (low < high) {
        int pivot = partition(arr, low, high); // 分割数组，获取枢轴位置
        quickSort(arr, low, pivot - 1); // 对左侧子数组进行递归排序
        quickSort(arr, pivot + 1, high); // 对右侧子数组进行递归排序
    }
}
#endif // __UTILS_H__