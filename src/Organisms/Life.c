#include <Organisms.h>
#include <Windows.h>
#include <Simulation.h>
#include <stdio.h>
#include <Draw.h>
#include <Life.h>
#include <time.h>

size_t GetBlacklist(wchar_t Cell);
static Organism *LocalOrganism;
static Win32_Terminal_Info TI;

size_t GetBlacklist(wchar_t Cell)
{
    wchar_t Blacklisted[] = {SOLID_OBJECT_SYMBOL};

    for (size_t i = 0; i < sizeof(Blacklisted); i++)
    {
        if (Cell == Blacklisted[i])
            return i;
    }
    return Normal;
}

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

void Move(Direction d)
{
    /*
        Simple rule:
        If the direction ahead of it (by 1) is occupied
        then consume it or leave it unless if it's a solid object
    */

    COORD Next_Coord = LocalOrganism->CURRENT;
    DWORD Dum;
    wchar_t Next_Cell;
    wchar_t Blank_Cell = 0x0f;
    wchar_t Sym = ORGANISM_SYMBOL;

    switch (d)
    {
    case DOWN:
        Next_Coord.Y--;
        break;
    case LEFT:
        Next_Coord.X--;
        break;
    case RIGHT:
        Next_Coord.X++;
        break;
    case UP:
        Next_Coord.Y++;
        break;
    }

    WaitForSingleObject(TI.hScreenMutex, INFINITE);
    ReadConsoleOutputCharacterW(TI.hConsoleOut, &Next_Cell, 1, Next_Coord, &Dum);

    switch (Next_Cell)
    {
    case ' ':
        WriteConsoleOutputCharacterW(TI.hConsoleOut, &Blank_Cell, 1, LocalOrganism->CURRENT, &Dum);
        WriteConsoleOutputAttribute(TI.hConsoleOut, 0, 1, LocalOrganism->CURRENT, &Dum);

        LocalOrganism->CURRENT = Next_Coord;
        WriteConsoleOutputAttribute(TI.hConsoleOut, &Blank_Cell, 1, Next_Coord, &Dum);
        WriteConsoleOutputCharacterW(TI.hConsoleOut, &Sym, 1, Next_Coord, &Dum);
        break;
    }
    ReleaseMutex(TI.hScreenMutex);

    Wait(500);
}

void Alive(void *o)
{
    UNUSED(o);
    LocalOrganism = Get_Organsisms();
    TI = Get_Info();

    Draw(ORGANISM_SYMBOL, LocalOrganism->Properties.Color, LocalOrganism->CURRENT);
    debug(("New Thread started."));
    // Neural Network?

    debug(("Organism POS: (%d,%d)", LocalOrganism->CURRENT.X, LocalOrganism->CURRENT.Y));
    while (WaitForSingleObject(TI.hRunMutex, 75L) == WAIT_TIMEOUT)
    {
        Move(RIGHT);
    }
}