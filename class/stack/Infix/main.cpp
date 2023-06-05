#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LnkStack.h"
#include "Infix.h"

int main()
{
	char s[100];
	//printf("input infix: ");
	scanf("%s", s);
	printf("result = %f\n", ComputeInfix(s));
}
