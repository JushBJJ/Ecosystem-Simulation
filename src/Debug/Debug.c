#include <stdio.h>
#include <Simulation.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <Debug.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>

void clear(void)
{
    DWORD dummy = 0;
    COORD Start = {0, 0};
    COORD x = GetconsoleSize();

    ClearBar();

    FillConsoleOutputCharacterW(GethConsoleOut(), L' ', (DWORD)(x.X * x.Y + 1), Start, &dummy);
    FillConsoleOutputAttribute(GethConsoleOut(), 0x0f, (DWORD)(x.X * x.Y + 1), Start, &dummy);
}

void ClearBar(void)
{
    COORD x = GetconsoleSize();
    DWORD dummy = 0;
    COORD Start = {0, x.Y};

    FillConsoleOutputCharacterW(GethConsoleOut(), L'\0', (DWORD)(x.X * 1), Start, &dummy);
}

void Log(const char *Message, ...)
{
#ifdef DEBUG
    FILE *f = fopen("Debug_Log.txt", "a");
    if (f == NULL)
    {
        clear();
        printf("ERROR WRITING FILE.\n");
        return;
    }

    va_list ap;
    va_start(ap, Message);
    vfprintf(f, Message, ap);
    va_end(ap);

    fclose(f);
#endif
    UNUSED(Message);
}