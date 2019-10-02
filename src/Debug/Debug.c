#include <stdio.h>
#include <Simulation.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <Debug.h>

void Log(char *Message)
{
    FILE *f = fopen("Debug_Log.txt", "a");

    if (f)
        fprintf(f, Message);
    else
    {
#ifdef Linux
        // Stop Threads

        clear();
        printf("[DEBUG]: UNABLE TO OPEN FILE.\n[DEBUG]: Last debug output: %s\n", Message);
#endif
#ifdef Windows
        // Stop threads

        clear();
        printf("[DEBUG]: UNABLE TO OPEN FILE.\n[DEBUG]: Last debug output: %s\n", Message);
#endif
    }

    fclose(f);
}
void Append(char *dest, char *src)
{
    if (strlen(src) + strlen(dest) > sizeof(dest))
    {
        debug(("Tried to append \"%s\" and \"%s\".\n\tlength of src: %d\n\tsize of dest: %d", dest, src, strlen(src), sizeof(dest)));
        return;
    }

    strcat(dest, src);
    return;
}