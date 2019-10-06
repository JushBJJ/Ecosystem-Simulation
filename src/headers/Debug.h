#ifndef DEBUG_H
#define DEBUG_H
#include <stdarg.h>

void Log(const char *Message, ...);
void vLog(const char *Message, va_list ap);
void Clear_Debug_File(void);

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

#define clear(void)                        \
    Win32_Terminal_Info TI_C = Get_Info(); \
    DWORD dummy = 0;                       \
    COORD Start = {0, 0};                  \
    FillConsoleOutputCharacterW(TI_C.hConsoleOut, L' ', (DWORD)(TI_C.consoleSize.X * TI_C.consoleSize.Y), Start, &dummy);
#endif
#endif