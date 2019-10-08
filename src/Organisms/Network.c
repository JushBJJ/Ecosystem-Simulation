#include <NeuralNetwork.h>
#include <Organisms.h>
#include <windows.h>
#include <Life.h>
#include <Simulation.h>

float Sigmoid(float x) { return 1 / (1 + exp((double)-x)); }

int NN(Organism *o, NeuralNetwork *LocalNN)
{
    UpdateOrganism(o);
    UpdateNeuralNetwork(LocalNN);

    Organism *x = o;
    COORD Next = o->CURRENT;
    wchar_t Next_Cell;
    DWORD Dum;

    SHORT upptr = o->CURRENT.Y - 1;
    SHORT downptr;
    SHORT rightptr;
    SHORT leftptr;

    int RangePtr;

    // Anyway to improve this? It looks like code hell

    Next.Y = o->CURRENT.Y - 1;
    while (Next.X <= o->CURRENT.X + 1)
    {
        Next.X = upptr;
        ReadConsoleOutputCharacterW(GethConsoleOut(), &Next_Cell, 1, Next, &Dum);
        LocalNN->Range[RangePtr] = Next_Cell;
        upptr++;
        RangePtr++;
    }
    Next.X = o->CURRENT.X - 1;

    Next.Y = o->CURRENT.Y;
    while (Next.X <= o->CURRENT.X + 1)
    {
        Next.X = downptr;
        ReadConsoleOutputCharacterW(GethConsoleOut(), &Next_Cell, 1, Next, &Dum);
        LocalNN->Range[RangePtr] = Next_Cell;
        downptr++;
        RangePtr++;

        if (downptr == o->CURRENT.X)
            downptr++;
    }

    Next.Y = o->CURRENT.Y + 1;
    while (Next.X <= o->CURRENT.X + 1)
    {
        Next.X = downptr;
        ReadConsoleOutputCharacterW(GethConsoleOut(), &Next_Cell, 1, Next, &Dum);
        LocalNN->Range[RangePtr] = Next_Cell;
        downptr++;
        RangePtr++;
    }
    Next.X = o->CURRENT.X - 1;

    
}