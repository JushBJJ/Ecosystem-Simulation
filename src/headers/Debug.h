#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG
#define debug(x) Log x
#else
#define debug(x) \
    do           \
    {            \
    } while (0);
#endif

#ifdef Linux
#define clear(void) printf("\033[H\033[J")
#endif
#ifdef Windows
#include <Windows.h>

#define clear(void)                     \
    Wi32_Terminal_Info TI = Get_Info(); \
    DWORD dummy = 0;                    \
    COORD Start = {0, 0};               \
    FillConsoleOutputCharacterW(TI.hConsoleOut, L' ', TI.consoleSize.X *TI.consoleSize.Y, Start, &dummy);
#endif

void Log(char *Message);
void Append(char *dest, char *src);
#endif