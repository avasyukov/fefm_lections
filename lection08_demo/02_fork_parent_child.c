#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    pid_t p;
    p = fork();

    if (p < 0) {
        perror("fork fail");
        exit(1);
    }
    else if (p == 0) {
        // child process because return value zero
        printf("Hello from Child!\n");
    } else {
        // parent process because return value non-zero
        printf("Hello from Parent!\n");
    }

    return 0;
}