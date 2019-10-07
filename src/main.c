#include <stdio.h>
#include <Simulation.h>
#include <Organisms.h>
#include <Draw.h>
#include <Debug.h>
#include <ctype.h>
#include <signal.h>
#include <conio.h>

static int Key;
static int ThreadPtr;
static Win32_Terminal_Info TI;

int GetNumThreads(void) { return ThreadPtr; }
int NewThread(void)
{
    ThreadPtr++;
    return ThreadPtr;
}

int main(void)
{
    Organism_p p;

    Clear_Debug_File();
    debug(("DEBUG MODE"));
    signal(SIGINT, Signal_Handler);
    signal(SIGSEGV, Signal_Handler_SEGMENTATION_FAULT);
    Init();

    Init_ID();
    New_Default_Area(true, false);

    p.Color = ORGANISM_COLOR_F + ORGANISM_COLOR_B;
    p.Current_Hunger = 100;
    p.Current_Thrist = 100;
    p.Max_Hunger = 100;
    p.Max_Thirst = 100;
    p.speed = 1;

    Create_Organism(p);

    while (tolower(Key) != 'q')
        Key = _getch();

    raise(2);
    return 0;
}

void ShutdownThreads(void)
{
    debug(("Shutting Down threads.."));
    TI = Init();

    while (ThreadPtr > 0)
    {
        ReleaseMutex(TI.hRunMutex);
        ThreadPtr--;
    }

    WaitForSingleObject(TI.hScreenMutex, INFINITE);
}

void Signal_Handler(int n)
{
    ShutdownThreads();
    Destroy_Objects(true);
    Destroy_Organisms(true);
    Reset_Areas(true);

    clear();
    clear();
    debug(("PROGRAM EXIT."));
    exit(0);
}

void Signal_Handler_SEGMENTATION_FAULT(int n)
{
    Signal_Handler(n);
    exit(0);
}