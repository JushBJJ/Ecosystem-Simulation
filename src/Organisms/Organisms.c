#include <stdio.h>
#include <Organisms.h>
#include <stdbool.h>
#include <Draw.h>
#include <Simulation.h>
#include <Windows.h>
#include <process.h>

static Organism *Organisms;
static bool Init_Organisms_;
static int Organisms_Count;
static size_t idptr;
static Win32_Terminal_Info TI;

Organism *Get_Organsisms(void) { return Organisms; }

void Destroy_Organisms(bool EXIT)
{
    debug(("Destroying Organisms..."));
    Organism *x;

    while (Organisms->next)
    {
        debug(("Destroying Organism ID: %d", Organisms->ID));
        x = Organisms->next;
        free(Organisms);
        Organisms = x;
    }

    if (EXIT)
        free(Organisms);
    else
        Organisms = NULL;

    debug(("Destroyed Organisms"));
}

void Create_Organism(Organism_p p)
{
    Organism *x;

    if (!Init_Organisms_)
    {
        Organisms = NULL;
        x = NULL;
        TI = Init();

        Organisms = malloc(sizeof *Organisms);
        Organisms->CURRENT.X = 10;
        Organisms->CURRENT.Y = 10;
        Organisms->next = NULL;

        Init_Organisms_ = true;
        debug(("Organism POS: (%d,%d)", Organisms->CURRENT.X, Organisms->CURRENT.Y));
        debug(("Initialized Organisms"));
    }
    while (Organisms->next)
    {
        x = Organisms;
        Organisms = Organisms->next;
    }

    Organisms->ID = idptr;
    Organisms->Properties = p;
    Organisms->Age = 0;
    Organisms->Children = 0;
    Organisms->Ready_To_Breed = false;
    Organisms->next = malloc(sizeof *Organisms);
    Organisms->prev = x;
    Organisms->Properties.Color = ORGANISM_COLOR_F;

    idptr++;
    Organisms_Count++;

    x = Organisms;

    NewThread();
    _beginthread(Alive, 0, &x);
}