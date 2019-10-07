#include <stdio.h>
#include <Simulation.h>
#include <Draw.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

static Area *Areas;
static size_t ID_ptr;

void Init_ID(void) { ID_ptr = 0; }

void Reset_Areas(bool EXIT)
{
    debug(("Resetting Areas..."));

    Area *x;
    while (Areas->prev)
    {
        x = Areas->prev;
        Areas = x;
    }
    while (Areas->next)
    {
        x = Areas->next;
        free(Areas);
        debug(("Destroyed Area: %d", ID_ptr));
        Areas = x;
        ID_ptr--;
    }

    if (EXIT)
    {
        free(Areas);
        debug(("Destroyed Area: %d", ID_ptr));
    }

    Init_ID();
    debug(("Resetted Areas."));
}

size_t New_Area(const size_t Length, const size_t Width, bool Construct, bool Reset)
{
    if (Reset)
        Reset_Areas(false);

    Area *x = Areas;
    while (Areas)
    {
        x = Areas;
        Areas = Areas->next;
    }

    ID_ptr++;

    Areas = malloc(sizeof *Areas);
    Areas->prev = x;
    Areas->next = NULL;

    Areas->Total_Animal_Population = 0;
    Areas->Total_Organism_Population = 0;
    Areas->Length = Length;
    Areas->Width = Width;
    Areas->ID = ID_ptr;

    if (Construct)
        Construct_Area(Areas);
    return Areas->ID;
}

size_t New_Default_Area(bool Construct, bool Reset)
{
    COORD x=GetconsoleSize();
    New_Area((size_t)x.X - 1, (size_t)x.Y - 1, Construct, Reset);
    return Areas->ID;
}

void Construct_Area(Area *a)
{
    debug(("Constructing Area..."));

    clear();

    Properties o;

    o.Damage = 0;
    o.Unbreakable = true;
    o.type = Solid_t;
    o.filled = true;
    o.Foreground_Color = SOLID_OBJECT_COLOR_F;
    o.Background_Color = SOLID_OBJECT_COLOR_B;
    o.x = 0;
    o.y = 0;

    debug(("Building objects..."));
    while (o.x <= a->Length)
    {
        PutObject(o);
        o.y = a->Width;
        PutObject(o);
        o.x++;
        o.y = 0;
    }

    o.x = 0;
    o.y = 1;

    while (o.y + 1 <= a->Width)
    {
        PutObject(o);
        o.x = a->Length;
        PutObject(o);
        o.y++;
        o.x = 0;
    }

    debug(("Finshed constructing Area %zu.", a->ID));
}