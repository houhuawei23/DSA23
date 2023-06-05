#include "queuenode.h"

void main()
{
    Queuenode* rear = CreateQueue();

    int i;
    for(i = 0; i < 10; i++)
    {
        In(&rear, i);
    }
        
    for(i = 0; i < 10; i++)
    {
        int result = Out(&rear);
        printf("%d\n", result);
    }
    printf("###\n");
    // again
    for(i = 0; i < 10; i++)
    {
        In(&rear, i);
    }
        
    for(i = 0; i < 10; i++)
    {
        int result = Out(&rear);
        printf("%d\n", result);
    }
}