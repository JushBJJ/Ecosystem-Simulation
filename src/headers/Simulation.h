#ifndef SIMULATION_H
#define SIMULATION_H

#include <Organisms.h>
#include <stdint.h>
#include <stddef.h>
#include <Debug.h>
#include <stdbool.h>

#ifdef Windows
#include <Windows.h>
typedef struct Win32_Terminal_Info
{
    HANDLE hConsoleOut;
    COORD consoleSize;
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    
    bool Vaild;
} Win32_Terminal_Info;

Win32_Terminal_Info Get_Info(void);
Win32_Terminal_Info Init(void);
#endif

#define Max_Length 1000
#define Max_Width 1000

typedef struct
{

    const size_t Length;
    const size_t Width;

    size_t Total_Population;
    size_t Total_Animal_Population;
    size_t Total_Organism_Population;

} Area;

Area New_Area(const int Length, const int Width);
Area New_Default_Area(void);
void Construct_Area(Area a);
void IMMEDIATE_ABORT(void);
#endif