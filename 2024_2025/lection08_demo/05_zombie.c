#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();

    if (pid > 0) {
        printf("%d: in parent process, child is %d\n", getpid(), pid);
    } else if (pid == 0) {
        sleep(3);
        printf("%d: in child process\n", getpid());
        sleep(60);
        printf("%d: exiting\n", getpid());
    }

    return 0;
}