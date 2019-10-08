#include <stdio.h>
#include <Organisms.h>
#include <stdbool.h>
#include <Draw.h>
#include <Simulation.h>
#include <Windows.h>
#include <process.h>

static Organism *Organisms;
static bool Init_Organisms_;
static size_t Organisms_Count;
static size_t idptr;

Organism *Get_Organisms(void) { return Organisms; }
void UpdateOrganism(Organism *o)
{
    Organism *x;
    while (Organisms->prev)
    {
        x = Organisms->prev;
        Organisms = x;
    }
    while (Organisms->next)
    {
        x = Organisms->next;
        if (Organisms->ID == o->ID)
            break;
        Organisms = x;
    }

    Organisms = o;
}

Organism *GetOrganism(size_t ID)
{
    Organism *x;
    while (Organisms->prev)
    {
        x = Organisms->prev;
        Organisms = x;
    }
    while (Organisms->next)
    {
        x = Organisms->next;
        if (Organisms->ID == ID)
            break;
        Organisms = x;
    }
    return Organisms;
}

Organism *LockOrganism(size_t ID)
{
    Organism *x;

    while (Organisms->prev)
    {
        x = Organisms->prev;
        Organisms = x;
    }

    while (Organisms->next)
    {
        x = Organisms->next;
        if (Organisms->ID == ID)
            break;
        Organisms = x;
    }

    if (Organisms->Locked == true)
        Organisms->Wrong = true;
    else
        Organisms->Locked = true;
    return Organisms;
}

void Destroy_Organisms(bool EXIT)
{
    debug(("Destroying Organisms..."));
    Organism *x;

    while (Organisms->prev)
    {
        x = Organisms->prev;
        Organisms = x;
    }

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

size_t Create_Organism(Organism_p p)
{
    Organism *x;

    if (!Init_Organisms_)
    {
        Organisms = NULL;
        x = NULL;

        Organisms = malloc(sizeof *Organisms);
        Organisms->next = NULL;
        Init_Organisms_ = true;
        debug(("Initialized Organisms"));
    }
    while (Organisms->prev)
    {
        x = Organisms->prev;
        Organisms = x;
    }

    while (Organisms->next)
    {
        x = Organisms->next;
        Organisms = x;
    }

    idptr++;
    Organisms_Count++;

    Organisms->ID = idptr;
    Organisms->Properties = p;
    Organisms->Age = 0;
    Organisms->Children = 0;
    Organisms->Ready_To_Breed = false;
    Organisms->next = malloc(sizeof *Organisms);
    Organisms->prev = x;
    Organisms->Properties.Color = ORGANISM_COLOR_F;
    Organisms->CURRENT = Organisms->Properties.BIRTH_POINT;

    return Organisms->ID;
}