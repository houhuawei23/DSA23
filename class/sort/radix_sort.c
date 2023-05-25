// 基数排序

#include <stdio.h>
#include <stdlib.h>

/*
基数排序：
    1. 从低位到高位，依次对每一位进行计数排序
    2. 计数排序的过程中，每一位的数字都是0-9，所以可以使用计数排序
    3. 从低位到高位，依次对每一位进行计数排序，最终得到的结果就是有序的
    4. 基数排序的时间复杂度为O(d(n+r))，其中d为位数，r为基数
    5. 基数排序的空间复杂度为O(n+r)
    6. 基数排序是稳定的排序算法
    7. 基数排序的缺点是需要占用大量的内存空间

时间复杂度：
    1. 最好情况：O(d(n+r))
    2. 最坏情况：O(d(n+r))
    3. 平均情况：O(d(n+r))
空间复杂度：O(n+r)
适用情况：


*/
void radix_sort(int *a, int n){
    int i, j, k, m, radix = 10;
    // count用于计数，bucket用于临时存储
    int *count, *bucket;
    count = (int *)malloc(sizeof(int) * radix);
    bucket = (int *)malloc(sizeof(int) * n);
    // 从低位到高位，依次对每一位进行计数排序
    for(m = 1; m <= 1000; m *= 10){
        for(i = 0; i < radix; i++){
            count[i] = 0;
        }
        for(i = 0; i < n; i++){
            k = (a[i] / m) % 10;
            count[k]++;
        }
        for(i = 1; i < radix; i++){
            count[i] += count[i - 1];
        }
        for(i = n - 1; i >= 0; i--){
            k = (a[i] / m) % 10;
            bucket[count[k] - 1] = a[i];
            count[k]--;
        }
        for(i = 0, j = 0; i < n; i++, j++){
            a[i] = bucket[j];
        }
    }
    free(count);
    free(bucket);
}

int main(){
    int a[10] = {73, 22, 93, 43, 55, 14, 28, 65, 39, 81};
    radix_sort(a, 10);
    for(int i = 0; i < 10; i++){
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}



