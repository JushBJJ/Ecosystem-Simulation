#include <stdio.h>

int main(void)
{
    int x = 5;

    for (int i = 0; i <= x; i++)
        printf("1: %d\n", i);

    for (int i = 0; i < x; i++)
        printf("2: %d\n", i);

    return 0;
}