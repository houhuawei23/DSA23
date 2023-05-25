// BFPTR 找出第k大元素，Blum-Floyd-Pratt-Rivest算法

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int BFPTR(int *a, int left, int right, int k){
    int i, j, pivot, temp;
    if(left == right){
        return a[left];
    }
    while(1){
        pivot = a[left + rand() % (right - left + 1)];
        for(i = left, j = right; i <= j;){
            while(a[i] < pivot){
                i++;
            }
            while(a[j] > pivot){
                j--;
            }
            if(i <= j){
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
                i++;
                j--;
            }
        }
        if(k <= j - left + 1){
            right = j;
        }else if(k > i - left){
            k -= i - left;
            left = i;
        }else{
            return pivot;
        }
    }
}


int main(){
    int a[MAX];
    int n, k;
    scanf("%d %d", &n, &k);
    for(int i = 0; i < n; i++){
        scanf("%d", &a[i]);
    }
    printf("%d\n", BFPTR(a, 0, n - 1, k));
    return 0;
}