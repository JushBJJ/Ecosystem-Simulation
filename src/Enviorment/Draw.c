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

size_t Get_Object_Num(void) { return Object_Count; }

void Destroy_Objects(bool EXIT)
{
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

}

void CursorPos(int x, int y)
{

    COORD ToPos = {(SHORT)x, (SHORT)y};

    SetConsoleCursorPosition(GethConsoleOut(), ToPos);
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

    WaitForSingleObject(GethScreenMutex(), INFINITE);
    WriteConsoleOutputCharacterW(GethConsoleOut(), &symbol, 1, Location, &Dum);
    WriteConsoleOutputAttribute(GethConsoleOut(), &Attribute, 1, Location, &Dum);
    ReleaseMutex(GethScreenMutex());
}