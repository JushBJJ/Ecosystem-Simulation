#ifndef LIFE_H
#define LIFE_H
#include <Windows.h>
#include <Simulation.h>

typedef int Direction;
enum Directions
{
    UPLEFT,
    UP,
    UPRIGHT,
    LEFT,
    RIGHT,
    DOWNLEFT,
    DOWN,
    DOWNRIGHT,
};

enum CellType
{
    Normal = ' ',
    Solid_Object = SOLID_OBJECT_SYMBOL,
    Liquid_Object = ')',
    Gas_Object = 'X'
};

void Move(Direction d, size_t ID);
#endif