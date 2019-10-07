#ifndef DRAW_H
#define DRAW_H

#include <Organisms.h>
#include <Simulation.h>
#include <stdint.h>
#include <stdbool.h>
#include <Windows.h>

enum Object_Types
{
    Solid_t,
    Liquid_t,
    Gas_t
};

typedef struct Properties
{
    int Damage;
    bool Unbreakable;

    int type;
    bool filled;

    WORD Foreground_Color;
    WORD Background_Color;

    size_t x;
    size_t y;
} Properties;

typedef struct Object
{
    Properties p;

    int x;
    int y;

    size_t Object_ID;
    struct Object *prev;
    struct Object *next;
} Object;

typedef struct
{
    int x;
    int y;
} COORD_X;

void CursorPos(int x, int y);
void PutObject(Properties o);
void Destroy_Objects(bool EXIT);
void Draw(wchar_t symbol, WORD Attribute, COORD Location);
COORD_X GetCursorRealPos(void);
size_t Get_Object_Num(void);
#endif