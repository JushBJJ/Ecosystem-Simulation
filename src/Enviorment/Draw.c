#include <Draw.h>
#include <stdint.h>
#include <Simulation.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

static Object *Objects;
static size_t Object_Count;
static size_t ID_ptr;
static bool Init_Objects_;
static Win32_Terminal_Info TI;

size_t Get_Object_Num(void) { return Object_Count; }

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

    TI = Init();
    COORD ToPos = {(SHORT)x, (SHORT)y};

    SetConsoleCursorPosition(TI.hConsoleOut, ToPos);
}

COORD_X GetCursorRealPos(void)
{
    COORD_X c;

    POINT pt;

    GetCursorPos(&pt);
    c.x = pt.x;
    c.y = pt.y;

    return c;

    // NEEDED

    return c;

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

    COORD f;
    f.X = (SHORT)Objects->x;
    f.Y = (SHORT)Objects->y;

    Draw('#', (WORD)(o.Foreground_Color + o.Background_Color), f);
}

void Draw(wchar_t symbol, WORD Attribute, COORD Location)
{
    DWORD Dum;
    TI = Get_Info();

    WaitForSingleObject(TI.hScreenMutex, INFINITE);
    WriteConsoleOutputCharacterW(TI.hConsoleOut, &symbol, 1, Location, &Dum);
    WriteConsoleOutputAttribute(TI.hConsoleOut, &Attribute, 1, Location, &Dum);
    ReleaseMutex(TI.hScreenMutex);
}