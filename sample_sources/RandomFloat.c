// Used to test getrandom function from Win32/multithreading_win32.c

#include <stdio.h>
#include <stdlib.h>

#define getrandom(min, max) (max-min)*((float)rand()/RAND_MAX) + min

int main(void)
{
    for (int i = 0; i < 10; i++)
        printf("Num: %f\n", getrandom(0, 1));

    return 0;
}