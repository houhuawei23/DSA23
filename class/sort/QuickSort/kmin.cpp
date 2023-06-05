#include <iostream>
#include <cstdio>
using namespace std;

int partition(int *A, int x, int y){
    int pivot = A[x];
    int i = x + 1;
    int j = y;
    while(i <= j){
        while(i <=j && A[i] <= pivot)
            i++;
        while(i <=j && A[j] > pivot)
            j--;
        if(i <j)
            swap(A[i], A[j]);
        
    }
    swap(A[x], A[j]);
    return j;

} 
int best_sort_k(int *A, int x, int y, int k)
{
    /*
    A 序列
    x 首索引
    y 末尾索引
    k 找第几大的元素
    */

    /********** Begin **********/
    int p = partition(A, x, y);
    if(p - x == k){
        return A[p];
    }
    else if(p - x > k-1){
        printf("partition1\n");
        return best_sort_k(A, x, p - 1, k);
    }
    else{
        printf("partition2\n");
        return best_sort_k(A, p + 1, y, k - (p - x) -1);
    }
    /********** End **********/
}

int main()
{
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];
    int k, k_value;
    cin >> k;
    k_value = best_sort_k(a, 0, n - 1, k-1);
    cout << k_value << endl;
    return 0;
}