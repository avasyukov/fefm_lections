#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t child_process_id = fork();

    if (child_process_id > 0) {
        // Fork returns a valid pid in the parent process. Parent executes this.

        // wait for the child process to complete
        int status;
        waitpid(child_process_id, &status, 0);

        // Child process is finished now.
    } else if (child_process_id == 0) {
        // Fork returns 0 in the child process. Child executes this.

        // new argv array for the child process
        char *argv[] = {"ls", "/opt", NULL};

        // now start executing some other program
        execv("/usr/bin/ls", argv);
    }

    return 0;
}