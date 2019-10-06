#include <Draw.h>
#include <stdint.h>
#include <Simulation.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef Windows
#include <Windows.h>
#endif

static Object *Objects;
static size_t Object_Count;
static size_t ID_ptr;
static bool Init_Objects_;
static Win32_Terminal_Info TI;

size_t Get_Object_Num(void) { return Object_Count; }

#ifdef Windows
static HANDLE hConsoleOut;
static COORD consoleSize;
static CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
static HANDLE hRunMutex;
static HANDLE hScreenMutex;
static bool Initialized;

Win32_Terminal_Info Get_Info(void)
{
    if (!Initialized)
    {
        TI = Init();
        return TI;
    }

    TI.hConsoleOut = hConsoleOut;
    TI.consoleSize = consoleSize;
    TI.csbiInfo = csbiInfo;
    TI.hScreenMutex = hScreenMutex;
    TI.hRunMutex = hRunMutex;
    return TI;
}

Win32_Terminal_Info Init(void)
{
    if (Initialized)
        return Get_Info();

    hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);
    consoleSize.X = csbiInfo.srWindow.Right;
    consoleSize.Y = csbiInfo.srWindow.Bottom;
    hScreenMutex = CreateMutexW(NULL, FALSE, NULL);
    hRunMutex = CreateMutexW(NULL, TRUE, NULL);

    Initialized = true;

    TI.hConsoleOut = hConsoleOut;
    TI.consoleSize = consoleSize;
    TI.csbiInfo = csbiInfo;
    TI.hScreenMutex = hScreenMutex;
    TI.hRunMutex = hRunMutex;
    return TI;
}
#endif

void Destroy_Objects(bool EXIT)
{
    debug(("Destroying Objects."));
    Object *x;

    while (Objects->next)
    {
        x = Objects->next;
        free(Objects);
        Objects = x;
    }

    if (EXIT)
    {
        free(Objects);
    }
    else
        Objects = NULL;

    debug(("Destroyed Objects"));
}

void CursorPos(int x, int y)
{
#ifdef Windows
    TI = Init();
    COORD ToPos = {(SHORT)x, (SHORT)y};

    SetConsoleCursorPosition(TI.hConsoleOut, ToPos);
#endif

#ifdef Linux
    printf("\033[%d;%dH", x, y);
#endif
}

COORD_X GetCursorRealPos(void)
{
    COORD_X c;
#ifdef Windows
    POINT pt;

    GetCursorPos(&pt);
    c.x = pt.x;
    c.y = pt.y;

    return c;
#endif
#ifdef Linux
    // NEEDED

    return c;
#endif
    c.x = -1;
    c.y = -1;

    return c;
}

void PutObject(Properties o)
{
    Object *x;

    if (!Init_Objects_)
    {
        Objects = NULL;
        x = NULL;

        Init_Objects_ = true;
        Objects = malloc(sizeof *Objects);
        Objects->next = NULL;
        debug(("Initialized Objects"));
    }
    while (Objects->next)
    {
        x = Objects;
        Objects = Objects->next;
    }

    Objects->Object_ID = ID_ptr;
    Objects->p = o;
    ID_ptr++;
    Objects->x = (int)o.x;
    Objects->y = (int)o.y;
    Objects->next = malloc(sizeof *Objects);
    Objects->next->next = NULL;
    Objects->prev = x;

    Object_Count++;

// Drawing
#ifdef Windows
    COORD f;
    TI = Get_Info();
    wchar_t Current_Cell = '#';
    WORD Current_Attr = o.Foreground_Color + o.Background_Color;
    DWORD Dum;

    f.X = (SHORT)Objects->x;
    f.Y = (SHORT)Objects->y;

    WaitForSingleObject(TI.hScreenMutex, INFINITE);
    WriteConsoleOutputCharacterW(TI.hConsoleOut, &Current_Cell, 1, f, &Dum);
    WriteConsoleOutputAttribute(TI.hConsoleOut, &Current_Attr, 1, f, &Dum);
    ReleaseMutex(TI.hScreenMutex);
#endif
#ifdef Linux

#endif
}