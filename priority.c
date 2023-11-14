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

void schedule_processes(struct Process processes[], int num_processes) {
    int current_time = 0;
    int running_process = -1;

    while (1) {
        int highest_priority = -1;

        // Find the highest-priority process that has arrived and not yet finished
        for (int i = 0; i < num_processes; i++) {
            if (processes[i].entry_time <= current_time && processes[i].execution_time > 0) {
                if (highest_priority == -1 || processes[i].priority < processes[highest_priority].priority) {
                    highest_priority = i;
                }
            }
        }

        if (highest_priority == -1) {
            // No processes to execute, all have finished
            break;
        }

        if (running_process != -1 && running_process != highest_priority) {
            // Preempt the currently running process if a higher-priority process is ready
            printf("Process ID %d preempted by Process ID %d.\n", processes[running_process].id, processes[highest_priority].id);
        }

        running_process = highest_priority;
        processes[running_process].execution_time--;
        printf("Executing Process ID: %d (Priority: %d, Time Left: %d)\n",
               processes[running_process].id, processes[running_process].priority, processes[running_process].execution_time);
        current_time++;
    }
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

    printf("Scheduling processes by priority with interruption:\n");
    schedule_processes(processes, NUM_PROCESSES);

    printf("All processes have been scheduled and executed.\n");

    return 0;
}
