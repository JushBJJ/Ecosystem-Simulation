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

static bool Opened_File;
static FILE *f;
void clear(void)
{
    DWORD dummy = 0;
    COORD Start = {0, 0};
    COORD x=GetconsoleSize();

    ClearBar();

    FillConsoleOutputCharacterW(GethConsoleOut(), L' ', (DWORD)(x.X * x.Y + 1), Start, &dummy);
    FillConsoleOutputAttribute(GethConsoleOut(), 0x0f, (DWORD)(x.X * x.Y + 1), Start, &dummy);
}

void Clear_Debug_File(void)
{
    if (Opened_File)
    {
        fclose(f);
        Opened_File = false;
    }

    f = fopen("Debug_Log.txt", "w");
    fclose(f);
}

void ClearBar(void)
{
    COORD x=GetconsoleSize();
    DWORD dummy = 0;
    COORD Start = {0, x.Y};

    FillConsoleOutputCharacterW(GethConsoleOut(), L'\0', (DWORD)(x.X * 1), Start, &dummy);
}

void Log(const char *Message, ...)
{
    f = fopen("Debug_Log.txt", "a");
    Opened_File = true;
    fprintf(f, "[DEBUG]: ");
    if (!f)
    {
        clear();
        printf("ERROR WRITING FILE.\n");
        return;
    }

    va_list ap;
    va_start(ap, Message);
    vLog(Message, ap);
    va_end(ap);

    fclose(f);
}

void vLog(const char *Message, va_list ap)
{
    int ptr = 0;
    while (Message[ptr])
    {
        switch (Message[ptr])
        {
        case '%':
            ptr++;
            switch (Message[ptr])
            {
            case 's':
                fprintf(f, "%s", va_arg(ap, char *));
                break;

            case 'd':
                fprintf(f, "%d", va_arg(ap, int));
                break;

            case 'z':
                ptr++;
                switch (Message[ptr])
                {
                case 'u':
                    fprintf(f, "%u", va_arg(ap, size_t));
                    break;

                default:
                    fprintf(f, "%c%c%c", '%', 'z', Message[ptr]);
                    break;
                }
                break;
            default:
                fprintf(f, "%c%c", '%', Message[ptr]);
                break;
            }
            break;

        default:
            fprintf(f, "%c", Message[ptr]);
            break;
        }
        ptr++;
    }
    fprintf(f, "\n");
}