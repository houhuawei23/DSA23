/*
g++ .\main.cpp .\SeqQueue.cpp
cat .\input1.txt | .\a.exe
*/
#include <stdio.h>
#include <stdlib.h>
#include "SeqQueue.h"
#include <string.h>
#pragma warning(disable:4996)

int main()
{
    int maxlen;
    scanf("%d", &maxlen);
    SeqQueue* sq=SQ_Create(maxlen);
    char dowhat[100];
    while(true) {
        scanf("%s", dowhat);
        if (!strcmp(dowhat,"in")) {
            T x;
            scanf("%d", &x);
            SQ_In(sq,x);
        }else if (!strcmp(dowhat,"out")) {
            T item;
            SQ_Out(sq, item);
        }
        else {
            break;
        }
    }
    int length=SQ_Length(sq);
    printf("Queue length: %d\n", length);
    printf("Queue data: ");
    SQ_Print(sq);
    SQ_Free(sq);
}
