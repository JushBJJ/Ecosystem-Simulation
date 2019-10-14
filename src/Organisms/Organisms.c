#include <stdio.h>
#include <Organisms.h>
#include <stdbool.h>
#include <Draw.h>
#include <Simulation.h>
#include <Windows.h>
#include <stdlib.h>
#include <process.h>

static Organism *Organisms;
static size_t Organisms_Count = 0;
static size_t idptr = 0;

Organism *Get_Organisms(void) { return Organisms; }
void UpdateOrganism(Organism *o)
{
    if ((Organisms + o->ID))
        memcpy((Organisms + o->ID), o, sizeof(Organism));
    else
        Log("UNABLE TO UPDATE ORGANISM ID %d\n", o->ID);
}

Organism *GetOrganism(size_t ID)
{
    if ((Organisms + ID))
        return (Organisms + ID);
    else
        return (Organism *)0x00;
}

void Destroy_Organisms(bool EXIT)
{
    size_t ptr = 1;

    while ((Organisms + ptr))
    {
        free((Organisms + ptr));
        ptr++;
    }

    if (EXIT)
        free((Organisms + 0));
    else
        memset((Organisms + 0), 0, sizeof(Organism));
}

size_t Create_Organism(Organism_p p)
{
    size_t Amount_Of_Organisms = Organisms_Count;
    size_t ptr = Amount_Of_Organisms;

    if (Amount_Of_Organisms == 0)
        Organisms = malloc(sizeof(Organism));

    idptr++;
    Organisms_Count++;

    (Organisms + ptr)->ID = Amount_Of_Organisms;
    (Organisms + ptr)->Properties = p;
    (Organisms + ptr)->Age = 0;
    (Organisms + ptr)->Children = 0;
    (Organisms + ptr)->Ready_To_Breed = false;
    (Organisms + ptr)->next = (Organism *)malloc(sizeof(Organism));
    (Organisms + ptr)->Properties.Color = ORGANISM_COLOR_F;
    (Organisms + ptr)->CURRENT = (Organisms + ptr)->Properties.BIRTH_POINT;

    return (Organisms + ptr)->ID;
}