#include <stdio.h>
#include <Simulation.h>
#include <Organisms.h>
#include <Draw.h>
#include <Debug.h>
#include <ctype.h>
#include <signal.h>
#include <stdlib.h>
#include <conio.h>
#include <Process.h>
#include <time.h>
#include <NeuralNetwork.h>
#include <string.h>

#define random_x (SHORT)((consoleSize.X - 2 - 2) * ((SHORT)rand() / RAND_MAX) + (SHORT)2);
#define random_y (SHORT)((consoleSize.Y - 2 - 2) * ((SHORT)rand() / RAND_MAX) + (SHORT)2);

void ClearDebugFile(void);
int NewReservedThread(void);

static int Key = 0;
static int ThreadPtr = 0;
static int ReservedThread = 0;
static int Seeds = 0;

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

int NewReservedThread(void)
{
    ReservedThread++;
    return ReservedThread;
}

void ClearDebugFile(void)
{
    FILE *f = fopen("Debug_Log.txt", "w");
    if (!f)
        raise(2);
    fclose(f);
}

int GetSeedPtr(void)
{
    Seeds++;
    return Seeds;
}

int main(void)
{
    Organism_p p;
    ClearDebugFile();

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
    p.BIRTH_POINT.X = random_x;
    p.BIRTH_POINT.Y = random_y;
    p.speed = 1;

    size_t ID;
    NeuralNetwork *NN;

    while (tolower(Key) != 'q')
    {
        Key = _getch();
        switch (tolower(Key))
        {
        case 'n':
            if (ThreadPtr < 20)
            {
                NewThread();
                ID = Create_Organism(p);
                _beginthread(Alive, 0, (void *)ID);
            }
            break;
        case 's':
            if (ThreadPtr + NewReservedThread() < 32)
            {
                ID = (size_t)(ThreadPtr + ReservedThread);
                _beginthread(Save_Strongest_NN, 0, (void *)ID);
            }
            break;
        case 'a':
            NewThread();
            ID = Create_Organism(p);
            NN = GetStrongestNeuralNetwork();
            NN->ID = ID;

            _beginthread(Alive, 0, (void *)ID);
            break;
        }
        p.BIRTH_POINT.X = random_x;
        p.BIRTH_POINT.Y = random_y;
    }
    raise(2);
    return 0;
}

void ShutdownThreads(void)
{

    while (ThreadPtr > 0)
    {
        ReleaseMutex(hRunMutex);
        ThreadPtr--;
    }

    WaitForSingleObject(hScreenMutex, INFINITE);
}

void Signal_Handler(int n)
{
    Log("Signal: %d\n", n);
    ShutdownThreads();

    Log("Shutted Down Threads.\n");
    clear();

    Destroy_Objects(true);
    Log("Destroyed Objects.\n");

    Destroy_Organisms(true);
    Log("Destoyed Organisms.\n");

    Destroy_NNS(true);
    Log("Destroyed Neural Networks.\n");

    Reset_Areas(true);
    Log("Destroyed Areas.\n");

    if (hScreenMutex)
        CloseHandle(hScreenMutex);
    if (hRunMutex)
        CloseHandle(hRunMutex);
    if (hConsoleOut)
        CloseHandle(hConsoleOut);
    Log("Exitted Program.\n");
    exit(0);
}