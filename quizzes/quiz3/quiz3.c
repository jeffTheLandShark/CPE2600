#include <stdio.h>

int count_access()
{
    static int counter = 0;
    counter++;
    return counter;
}

int main(void)
{
    printf("access: %d",count_access());
    printf("access: %d",count_access());
    printf("access: %d",count_access());

    return 0;
}
