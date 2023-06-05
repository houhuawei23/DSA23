#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LnkStack.h"
#include "Postfix.h"
int main()
{
    char s[100];
    // printf("input postfix: ");
    scanf("%s", s);
    printf("result = %f", ComputePostfix(s));
    //system("PAUSE");
    return 0;
}
