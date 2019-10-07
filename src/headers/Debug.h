#ifndef DEBUG_H
#define DEBUG_H
#include <stdarg.h>
#include <Windows.h>
#include <Simulation.h>

void Log(const char *Message, ...);
void vLog(const char *Message, va_list ap);
void Clear_Debug_File(void);
void clear(void);

#ifdef DEBUG
#define debug(x) Log x
#else
#define debug(x) \
    do           \
    {            \
    } while (0); \
    UNUSED(x);
#endif
#endif