#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main() {
    int arr[] = {4, 2, 7, 1, 5, 9, 3};
    int len = sizeof(arr) / sizeof(arr[0]);

    int median = get_med(arr, len);
    printf("Median: %d\n", median);

    quickSort(arr, 0, len - 1);
    printf("Sorted array: ");
    for (int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
    return 0;
}