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

void schedule_round_robin(struct Process processes[], int num_processes, int quantum) {
    int current_time = 0;
    int *remaining_time = (int *)malloc(num_processes * sizeof(int));

    // Initialize remaining_time for all processes
    for (int i = 0; i < num_processes; i++) {
        remaining_time[i] = processes[i].execution_time;
    }

    int completed_processes = 0;
    int process_index = 0;

    while (completed_processes < num_processes) {
        for (int i = 0; i < num_processes; i++) {
            if (remaining_time[i] > 0 && processes[i].entry_time <= current_time) {
                int execute_time = remaining_time[i] > quantum ? quantum : remaining_time[i];
                printf("Executing Process ID: %d (Time Left: %d)\n",
                       processes[i].id, remaining_time[i]);

                // Simulate execution of the process
                sleep(execute_time);
                current_time += execute_time;
                remaining_time[i] -= execute_time;

                if (remaining_time[i] == 0) {
                    completed_processes++;
                    printf("Process ID %d has completed execution.\n", processes[i].id);
                }
            }
        }
    }

    free(remaining_time);
}

int main() {
    struct Process processes[NUM_PROCESSES];
    for (int i = 0; i < NUM_PROCESSES; i++) {
        if (scanf("%d %d %d %d", &processes[i].id, &processes[i].entry_time, &processes[i].execution_time, &processes[i].priority) != 4) {
            fprintf(stderr, "Error reading process information.\n");
            exit(1);
        }
    }

    printf("Processes received from the generator:\n");
    for (int i = 0; i < NUM_PROCESSES; i++) {
        printf("Process ID: %d, Entry Time: %d, Execution Time: %d, Priority: %d\n",
               processes[i].id, processes[i].entry_time, processes[i].execution_time, processes[i].priority);
    }

    int quantum = 3;

    printf("Scheduling processes using Round Robin with time quantum %d:\n", quantum);
    schedule_round_robin(processes, NUM_PROCESSES, quantum);

    printf("All processes have been scheduled and executed.\n");

    return 0;
}
