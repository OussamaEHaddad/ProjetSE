#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/prctl.h>
#include <string.h>
#include <time.h>

#define NUM_PROCESSES 10

struct Process {
    int id;
    int entry_time;
    int execution_time;
    int priority;
};

int compare_entry_time(const void *a, const void *b) {
    return ((struct Process *)a)->entry_time - ((struct Process *)b)->entry_time;
}

int main() {
    // Make the parent process a subreaper
    prctl(PR_SET_CHILD_SUBREAPER, 1, 0, 0, 0);

    struct Process processes[NUM_PROCESSES];

    srand(time(NULL));

    for (int i = 0; i < NUM_PROCESSES; i++) {
        processes[i].id = i + 1;
        processes[i].entry_time = rand() % 10;
        processes[i].execution_time = rand() % 10 + 1;
        processes[i].priority = rand() % 5;
    }

    // Sort processes by entry time
    qsort(processes, NUM_PROCESSES, sizeof(struct Process), compare_entry_time);

    for (int i = 0; i < NUM_PROCESSES; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            exit(1);
        } else if (pid == 0) { // Child process
            printf("PID: %d, Entry Time: %d, Execution Time: %d, Priority: %d\n",
                   getpid(), processes[i].entry_time, processes[i].execution_time, processes[i].priority);

            // Simulate execution time
            sleep(processes[i].execution_time);

            printf("ID: %d has completed execution.\n", getpid());
            exit(0);
        } else {
            int status;
            waitpid(pid, &status, 0); // Wait for the child process to complete before forking the next one
        }
    }

    return 0;
}
