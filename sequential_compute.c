#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int readNumber(int fd, int *num)
{
    char buf[256], *p = buf;
    int n, val = 0, sign = 1;

    while ((n = read(fd, p, 1)) > 0)
    {
        if (*p == ',' || *p == '\n' || *p == 0)
            break;
        if (*p == '-')
            sign = -1;
        else
            val = val * 10 + (*p - '0');
        p++;
    }
    *num = val * sign;
    return n;
}

int add(int a, int b)
{
    return a + b;
}

int sequential_compute(char *filepath, int (*f)(int, int))
{
    int fd = open(filepath, O_RDONLY);
    if (fd < 0)
    {
        printf(1, "Couldn't open file\n");
        exit();
    }

    int result, temp;
    readNumber(fd, &result);

    while (readNumber(fd, &temp) > 0)
    {
        result = f(result, temp);
    }

    close(fd);
    return result;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf(1, "Usage: %s <file>\n", argv[0]);
        exit();
    }

    int result = sequential_compute(argv[1], add);
    printf(1, "Result: %d\n", result);

    exit();
}
