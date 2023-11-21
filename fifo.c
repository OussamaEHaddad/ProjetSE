#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NUM_PROCESSES 10

struct Process {
    int id;
    int entry_time;
    int execution_time;
    int priority;
};

// Function to compare processes based on entry time
int compare_entry_time(const void *a, const void *b) {
    return ((struct Process *)a)->entry_time - ((struct Process *)b)->entry_time;
}

int main() {
    struct Process processes[NUM_PROCESSES];
    for (int i = 0; i < NUM_PROCESSES; i++) {
        if (scanf("%d %d %d %d", &processes[i].id, &processes[i].entry_time, &processes[i].execution_time, &processes[i].priority) != 4) {
            fprintf(stderr, "Error reading process information.\n");
            exit(1);
        }
    }

    // Sort processes by entry time
    qsort(processes, NUM_PROCESSES, sizeof(struct Process), compare_entry_time);

    printf("Processes received from the generator:\n");
    for (int i = 0; i < NUM_PROCESSES; i++) {
        printf("Process ID: %d, Entry Time: %d, Execution Time: %d, Priority: %d\n",
               processes[i].id, processes[i].entry_time, processes[i].execution_time, processes[i].priority);
    }

    printf("Scheduling processes using FIFO:\n");

    int current_time = 0;
    for (int i = 0; i < NUM_PROCESSES; i++) {
        if (processes[i].entry_time > current_time) {
            current_time = processes[i].entry_time;
        }
        printf("Executing Process ID: %d\n", processes[i].id);
        sleep(processes[i].execution_time);
        current_time += processes[i].execution_time;
    }

    printf("All processes have been scheduled and executed.\n");

    return 0;
}
