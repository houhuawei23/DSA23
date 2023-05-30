#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CLnkQueue.h"
#pragma warning(disable:4996)

int main()
{
    LNode* rear=CLQ_Create();
    char dowhat[100];
    while(true) {
        scanf("%s", dowhat);
        if (!strcmp(dowhat,"in")) {
            T x;
            scanf("%d", &x);
            CLQ_In(rear,x);
        }else if (!strcmp(dowhat,"out")) {
            T item;
            CLQ_Out(rear, item);
        }
        else {
            break;
        }
    }
    int length=CLQ_Length(rear);
    printf("Queue length: %d\n", length);
    printf("Queue data: ");
    CLQ_Print(rear);
    CLQ_Free(rear);
}
