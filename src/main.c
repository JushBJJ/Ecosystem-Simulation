#include <stdio.h>
#include <Simulation.h>
#include <Organisms.h>
#include <Draw.h>
#include <Debug.h>
#include <ctype.h>
#include <signal.h>
#include <conio.h>
#include <Process.h>

static int Key;
static int ThreadPtr;

HANDLE hConsoleOut;
COORD consoleSize;
CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
HANDLE hRunMutex;
HANDLE hScreenMutex;

int GetNumThreads(void) { return ThreadPtr; }
HANDLE GethConsoleOut(void) { return hConsoleOut; }
COORD GetconsoleSize(void) { return consoleSize; }
CONSOLE_SCREEN_BUFFER_INFO GetcsbiInfo(void) { return csbiInfo; }
HANDLE GethScreenMutex(void) { return hScreenMutex; }
HANDLE GethRunMutex(void) { return hRunMutex; }

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

    signal(SIGABRT, Signal_Handler);
    signal(SIGFPE, Signal_Handler);
    signal(SIGILL, Signal_Handler);
    signal(SIGSEGV, Signal_Handler);
    signal(SIGINT, Signal_Handler);
    signal(SIGTERM, Signal_Handler);

    hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);
    consoleSize.X = csbiInfo.srWindow.Right;
    consoleSize.Y = csbiInfo.srWindow.Bottom;
    clear();
    hScreenMutex = CreateMutexW(NULL, FALSE, NULL);
    hRunMutex = CreateMutexW(NULL, TRUE, NULL);

    ThreadPtr = 0;

    Init_ID();
    New_Default_Area(true, false);

    p.Color = ORGANISM_COLOR_F + ORGANISM_COLOR_B;
    p.Current_Hunger = 100;
    p.Current_Thrist = 100;
    p.Max_Hunger = 100;
    p.Max_Thirst = 100;
    p.BIRTH_POINT.X = 10;
    p.BIRTH_POINT.Y = 10;
    p.speed = 1;

    size_t ID;

    while (tolower(Key) != 'q')
    {
        Key = _getch();
        switch (tolower(Key))
        {
        case 'n':
            if (ThreadPtr < 32)
            {
                NewThread();
                ID = Create_Organism(p);
                _beginthread(Alive, 0, (void *)ID);
                p.BIRTH_POINT.Y++;
            }
            break;
        }
    }
    raise(2);
    return 0;
}

void ShutdownThreads(void)
{
    debug(("Shutting Down threads.."));

    while (ThreadPtr > 0)
    {
        ReleaseMutex(hRunMutex);
        ThreadPtr--;
    }

    WaitForSingleObject(hScreenMutex, INFINITE);
}

void Signal_Handler(int n)
{
    ShutdownThreads();
    clear();
    Destroy_Objects(true);
    Destroy_Organisms(true);
    Reset_Areas(true);

    if (hScreenMutex)
        CloseHandle(hScreenMutex);
    if (hRunMutex)
        CloseHandle(hRunMutex);
    if (hConsoleOut)
        CloseHandle(hConsoleOut);

    debug(("EXIT NUM: %d", n));
    exit(0);
}