#ifndef LIFE_H
#define LIFE_H
typedef int Direction;
enum Directions
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

enum CellType
{
    Normal,
    Solid_Object,
    Liquid_Object,
    Gas_Object
};

void Move(Direction d);
#endif