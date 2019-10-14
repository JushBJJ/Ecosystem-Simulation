#include <Organisms.h>
#include <Windows.h>
#include <Simulation.h>
#include <stdio.h>
#include <Draw.h>
#include <Life.h>
#include <stdbool.h>
#include <time.h>
#include <process.h>
#include <conio.h>
#include <NeuralNetwork.h>

Organism *LocalOrganism;
COORD Next_Coord;
DWORD Dum;
wchar_t Next_Cell;
wchar_t Blank_Cell = 0x20;
wchar_t Sym = ORGANISM_SYMBOL;
wchar_t Attr = ORGANISM_COLOR_F;

void Wait(long int milliseconds)
{
    clock_t pin = clock();
    clock_t now;
    long int msec = 0;

    do
    {
        now = clock() - pin;
        msec = now * 1000 / CLOCKS_PER_SEC;
    } while (msec < milliseconds);
}

void Move(Direction d, size_t ID)
{
    /*
        Simple rule:
        If the direction ahead of it (by 1) is occupied
        then consume it or leave it unless if it's a solid object
    */
    Organism *o = GetOrganism(ID);
    NeuralNetwork *NN = GetNN(ID);

    LocalOrganism = o;
    Next_Coord = o->CURRENT;

    switch (d)
    {
    case DOWN:
        Next_Coord.Y++;
        break;
    case LEFT:
        Next_Coord.X--;
        break;
    case RIGHT:
        Next_Coord.X++;
        break;
    case UP:
        Next_Coord.Y--;
        break;
    case UPLEFT:
        Next_Coord.Y--;
        Next_Coord.X--;
        break;
    case UPRIGHT:
        Next_Coord.Y--;
        Next_Coord.X++;
        break;
    case DOWNLEFT:
        Next_Coord.Y++;
        Next_Coord.X--;
        break;
    case DOWNRIGHT:
        Next_Coord.Y++;
        Next_Coord.X++;
        break;
    }

    ReadConsoleOutputCharacterW(GethConsoleOut(), &Next_Cell, 1, Next_Coord, &Dum);

    switch (Next_Cell)
    {
    case Normal:
        NN->Fitness += 100;
        WriteConsoleOutputCharacterW(GethConsoleOut(), &Blank_Cell, 1, LocalOrganism->CURRENT, &Dum);
        WriteConsoleOutputAttribute(GethConsoleOut(), 0, 1, LocalOrganism->CURRENT, &Dum);

        LocalOrganism->CURRENT = Next_Coord;
        WriteConsoleOutputCharacterW(GethConsoleOut(), &Sym, 1, Next_Coord, &Dum);
        WriteConsoleOutputAttribute(GethConsoleOut(), &Attr, 1, Next_Coord, &Dum);
        break;
    default:
        break;
    }
    ReleaseMutex(GethScreenMutex());
    UpdateOrganism(LocalOrganism);
}

void Alive(void *x)
{
    size_t ID = (size_t)x;

    LocalOrganism = GetOrganism(ID);
    NeuralNetwork *LocalNN = NewNN(ID);

    do
    {
        WaitForSingleObject(GethScreenMutex(), INFINITE);
        NN(LocalOrganism, LocalNN);
        Forward(LocalNN);
    } while (WaitForSingleObject(GethRunMutex(), 75L) == WAIT_TIMEOUT);
}
