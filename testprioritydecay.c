#include "types.h"
#include "user.h"
#include "stat.h"

// we want to test the priority of the processes.
// to set priorities we use the custom setpriority(pid, priority) syscall
// to check processes table we use printptable() syscall

void create_process(int n) {
    if (n > 0) {
        int pid = fork();
        setpriority(pid, n);
        if (pid == 0) {
            sleep(100);
            // if process is even sleep more (for the priority to decay)
            if (n % 2 == 0) {
                sleep(3000);
            }
            printf(1, "\n\nThis is child process with id %d\n", getpid());

            printptable();
            exit();
            wait();
        } else {
            create_process(n - 1);
            wait();
        }
    }
}

int main(int argc, char *argv[])
{

    // check if the number of arguments is correct
    if (argc != 3)
    {
        printf(1, "Usage: testpriority <process count> <modulus>\n tip: try 10 5\n another tip: Have your process count higher than the modulus to see effect\n");
        exit();
    }

    // create processes according to arguments given
    int process_count = atoi(argv[1]);
    int priority_modulus = atoi(argv[2]);
    create_process(process_count); 

    exit();
}