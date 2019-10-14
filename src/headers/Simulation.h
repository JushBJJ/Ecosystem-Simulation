#ifndef SIMULATION_H
#define SIMULATION_H

#include <Organisms.h>
#include <stdint.h>
#include <stddef.h>
#include <Debug.h>
#include <stdbool.h>
#include <Windows.h>

#define SOLID_OBJECT_SYMBOL '#'
#define SOLID_OBJECT_COLOR_F FOREGROUND_BLUE
#define SOLID_OBJECT_COLOR_B BACKGROUND_BLUE

#define ORGANISM_SYMBOL '@'
#define ORGANISM_COLOR_F FOREGROUND_GREEN
#define ORGANISM_COLOR_B 0x0f

#define UNUSED(x) (void)(x)

void Signal_Handler(int n);
void Signal_Handler_SEGMENTATION_FAULT(int n);

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

void ShutdownThreads(void);
int NewThread(void);
void Init_ID(void);
void Construct_Area(Area *a);
void IMMEDIATE_ABORT(void);
void Reset_Areas(bool EXIT);
void Wait(long int milliseconds);
int GetSeedPtr(void);

int GetNumThreads(void);
HANDLE GethConsoleOut(void);
COORD GetconsoleSize(void);
CONSOLE_SCREEN_BUFFER_INFO GetcsbiInfo(void);
HANDLE GethScreenMutex(void);
HANDLE GethRunMutex(void);

#endif