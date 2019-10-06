#ifndef SIMULATION_H
#define SIMULATION_H

#include <Organisms.h>
#include <stdint.h>
#include <stddef.h>
#include <Debug.h>
#include <stdbool.h>

void Signal_Handler(int n);
void Signal_Handler_SEGMENTATION_FAULT(int n);

#ifdef Windows
#include <Windows.h>
typedef struct Win32_Terminal_Info
{
    HANDLE hConsoleOut;
    COORD consoleSize;
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    HANDLE hScreenMutex; // N
    HANDLE hRunMutex;    // N
    int ThreadNr;        // N

    bool Vaild;
} Win32_Terminal_Info;

Win32_Terminal_Info Get_Info(void);
Win32_Terminal_Info Init(void);
#endif

#define Max_Length 1000
#define Max_Width 1000

typedef struct Area
{
    size_t Total_Population;
    size_t Total_Animal_Population;
    size_t Total_Organism_Population;

    size_t Length;
    size_t Width;

    size_t ID;
    struct Area *next;
    struct Area *prev;
} Area;

size_t New_Area(const size_t Length, const size_t Width, bool Construct, bool Reset);
size_t New_Default_Area(bool Construct, bool Reset);

void Init_ID(void);
void Construct_Area(Area *a);
void IMMEDIATE_ABORT(void);
void Reset_Areas(bool EXIT);
#endif