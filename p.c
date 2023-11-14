#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    // Fork a new process
    pid = fork();

    if (pid < 0) {
        // Error occurred while forking
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {
        // This code is executed by the child process
        printf("Child process: PID = %d\n", getpid());

        // Enter into an infinite loop
        while (1) {
            // Perform some long-running task here
            // For example, you can simulate a task by sleeping
            sleep(1);
        }
    } else {
        // This code is executed by the parent process
        printf("Parent process: PID = %d\n", getpid());

        // Wait for the child to complete
        wait(NULL);
    }

    return 0;
}
