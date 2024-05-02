#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf(1, "Usage: setpriority <pid> <priority>\n");
        exit();
    }

    int pid = atoi(argv[1]);
    int priority = atoi(argv[2]);
    int old = setpriority(pid, priority);

    if (old >= 0)
    {
        printf(1, "Priority changed from %d to %d fr\n", old, priority);
    }
    else
    {
        printf(1, "Failed to set priority\n");
    }
    exit();
}