#include <stdio.h>
#include <Simulation.h>
#ifdef Windows
#include <Windows.h>
#endif
#ifdef Linux
// Define terminal drawing functions or library
#endif

Area New_Area(const int Length, const int Width)
{
    Area New = {Length, Width};
    return New;
}

Area New_Default_Area(void)
{
    Area Default = {10, 10};
    return Default;
}

void Construct_Area(Area a)
{
#ifdef Windows
clear();
// Make functions to make walls and stuff
#endif
}