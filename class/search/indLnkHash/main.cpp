#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "indLnkHash.h"
#pragma warning(disable:4996)

int main()
{
    int n;
    scanf("%d",&n);
    LHTable* pt=ILH_Create(n);
    char dowhat[100];
    while(true) {
        scanf("%s", dowhat);
        if (!strcmp(dowhat,"insert")) {
            int x;
            scanf("%d", &x);
            ILH_InsKey(pt, x);
        }else if (!strcmp(dowhat,"delete")) {
            int x;
            scanf("%d", &x);
            ILH_DelKey(pt, x);
        }
        else {
            break;
        }
    }
    ILH_Print(pt);
    ILH_Free(pt);
    //system("PAUSE");
}
