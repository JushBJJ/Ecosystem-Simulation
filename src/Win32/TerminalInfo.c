#include <Simulation.h>
#include <stdbool.h>
#include <Debug.h>

#ifdef Windows
#include <Windows.h>

static HANDLE hConsoleOut;
static COORD consoleSize;
static CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
static bool Initialized;

Win32_Terminal_Info Get_Info(void)
{
    Win32_Terminal_Info TI;

    if (!Initialized)
    {
        TI = Init();
        return TI;
    }

    TI.hConsoleOut = hConsoleOut;
    TI.consoleSize = consoleSize;
    TI.csbiInfo = csbiInfo;
    return TI;
}

Win32_Terminal_Info Init(void)
{
    Win32_Terminal_Info TI;

    if (Initialized)
        return Get_Info();

    hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);
    consoleSize.X = csbiInfo.srWindow.Right;
    consoleSize.Y = csbiInfo.srWindws.Bottom;

    Initialized = true;
}
#endif