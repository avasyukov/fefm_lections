#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t p = fork();

    if (p < 0) {
        perror("fork fail");
        return p;
    }

    // let's make some fun
//    fork();
//    fork();

    printf("Hello world! process_id(pid) = %d \n", getpid());

    return 0;
}