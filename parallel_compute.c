#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int
add(int a, int b){
    return a + b;
}

int
multiply(int a, int b){
    return a * b;
}

int 
readNumber(int fd, int *num) {
    char buf[256];
    char *p = buf;
    int n, val = 0, sign = 1;

    // Read one byte at a time
    while((n = read(fd, p, 1)) > 0) {
        // Check for comma or EOF to stop reading the number
        if(*p == ',' || *p == '\n' || *p == 0) break;
        if(*p == '-') sign = -1; // Negative number
        else val = val * 10 + (*p - '0');
        p++;
    }
    *num = val * sign;
    return n; // Return read status
}

int
parallel_compute(char * filePath, int n_proc, int (*f)(int,int)){
    int fd;
    if((fd = open(filePath, O_RDONLY )) < 0){        
        printf(1, "parallel_compute: cannot open %s\n", filePath);
        exit();
    }

    int count =0;
    int a;
    while(readNumber(fd, &a) > 0) {
        count++;
    }

    // reset file pointer
    close(fd);
    if((fd = open(filePath, O_RDONLY )) < 0){        
        printf(1, "parallel_compute: cannot open %s\n", filePath);
        exit();
    }

    // Read the numbers from the file into an array
    int *numbers = (int *)malloc(count * sizeof(int));
    
    for(int i = 0; i < count; i++) {
        readNumber(fd, &numbers[i]);
    }

    // Close the file
    close(fd);

    int size = count/n_proc;

    if(size == 0){
        size = 1;
        n_proc = count;
    }

    // array for results
    int *results = (int *)malloc(n_proc * sizeof(int));

    // create n_proc pipes
    int **pipes = (int **)malloc(n_proc * sizeof(int *));
    for (int i = 0; i < n_proc; i++)
    {
        pipes[i] = (int *)malloc(2 * sizeof(int));
        pipe(pipes[i]);
        // test if pipe was created successfully
        if(pipes[i][0] == -1 || pipes[i][1] == -1){
            printf(1,"Error creating pipe\n");
            return -1;
        }
    }

    for(int i = 0; i < n_proc; i++){
        
        int pid = fork();
        if(pid == 0){
            // close pipe read end
            close(pipes[i][0]);
            // child process
            int start = i * size;
            // last index for last process is count - 1
            int end = (i == (n_proc - 1) )? count : (start + size);
            int result = numbers[start];
            for (int j = start + 1; j < end; j++)
            {
                result = f(result, numbers[j]);
            }
            
            // pass value to parent using pipe
            write(pipes[i][1], &result, sizeof(int));
            // close pipe write end
            close(pipes[i][1]);
            // exit child process
            exit();

        }else{
            // close pipe write end
            close(pipes[i][1]);
        }
    
    }

    // wait for all child processes to finish
    while(1){
        int child = wait();
        if(child == -1){
            break;
        }
    }
    
    // read results from pipes
    for (int i = 0; i < n_proc; i++)
    {
        read(pipes[i][0], &results[i], sizeof(int));
        close(pipes[i][0]);
    }

    // combine results
    int finalResult = results[0];
    for (int i = 1; i < n_proc; i++)
    {
        finalResult = f(finalResult, results[i]);
    }

    // free memory
    free(numbers);
    free(results);
    for (int i = 0; i < n_proc; i++)
    {
        free(pipes[i]);
    }
    free(pipes);

    return finalResult; 

}

int
main(int argc, char *argv[])
{
    // syntax of calling parallel_compute is parallel_compute <file_path> <n_proc>
    if(argc <= 2){
        // Could provide a better error message here by calling save with unique arguments
        printf(1, "parallel_compute: not enough arguments\n");
        exit();
    }

    int n_proc = atoi(argv[2]);
    if(n_proc <= 0){
        printf(1, "parallel_compute: invalid number of processes\n");
        exit();
    }

    int result = parallel_compute(argv[1], n_proc, add);
    printf(1, "Result of parallel_compute: %d\n", result);
    exit();
}