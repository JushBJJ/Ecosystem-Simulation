#ifndef Organisms_H
#define Organisms_H

#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <Windows.h>

typedef struct Organism_p
{

    size_t speed; // Measured at Cells Per Second
    size_t health;

    size_t Max_Hunger;
    size_t Max_Thirst;

    size_t Current_Hunger;
    size_t Current_Thrist;

    COORD BIRTH_POINT;

    WORD Color;
} Organism_p;

typedef struct Organism
{
    size_t ID;
    Organism_p Properties;

    size_t Children;
    size_t Age;
    bool Ready_To_Breed;

    COORD CURRENT;

    struct Organism *next;
    struct Organism *prev;
} Organism;

Organism *Get_Organisms(void);
Organism *GetOrganism(size_t ID);
void Destroy_Organisms(bool EXIT);
size_t Create_Organism(Organism_p p);
void UpdateOrganism(Organism *o);
void Alive(void *x);

#endif