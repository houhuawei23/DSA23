#include <stdlib.h>
#include <stdio.h>

int main(){
    int a[7] = {7,8,30,11,18,9,14};

    int hashnum[7] = {0};
    for(int i=0;i<7;i++){
        hashnum[i]= hash(a[i]);
    }
    for(int i=0; i<7; i++){
        printf("%d ",a[i]);
    }
    printf("\n");
    for(int i=0;i<7;i++){
        printf("%d ",hashnum[i]);
    }
    printf("\n");
}

int hash(int key){
    return (key*3)%7;
}