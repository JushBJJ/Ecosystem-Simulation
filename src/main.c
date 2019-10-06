#include <stdio.h>
#include <Simulation.h>
#include <Draw.h>
#include <Debug.h>
#include <ctype.h>
#include <signal.h>
#ifdef Windows
#include <conio.h>
#endif

static int Key;

int main(void)
{
    Clear_Debug_File();
    debug(("DEBUG MODE"));
    signal(SIGINT, Signal_Handler);
    signal(SIGSEGV, Signal_Handler_SEGMENTATION_FAULT);

#ifdef Windows
    Init();
#endif

    Init_ID();
    New_Default_Area(true, false);

#ifdef Windows
    while (tolower(Key) != 'q')
        Key = _getch();
#endif

    raise(2);
    return 0;
}

void Signal_Handler(int n)
{
    Destroy_Objects(true);
    Reset_Areas(true);

    clear();
    debug(("PROGRAM EXIT."));
    printf("SIGNAL: %d\n", n);
    exit(0);
}

void Signal_Handler_SEGMENTATION_FAULT(int n)
{
    clear();

    printf("Uh oh, SEGMENTATION FAULT AHAHHAHHA\n");
    printf("Num: %d\n", n);
    debug(("Segmentation Fault. Num: %d", n));

    Destroy_Objects(true);
    Reset_Areas(true);
    exit(0);
}