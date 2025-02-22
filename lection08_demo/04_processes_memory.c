#include <stdio.h>
#include <unistd.h>

int value;

int main()
{
    int pid = fork();

    value = 0;

    if (pid > 0) {
        printf("%d: in parent process\n", getpid());
        sleep(3);
    } else if (pid == 0) {
        printf("%d: in child process\n", getpid());
    }

    printf("%d: value = %d\n", getpid(), value);
    value++;
    printf("%d: value = %d\n", getpid(), value);

    return 0;
}