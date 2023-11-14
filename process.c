#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_PROCESSES 10

struct Process {
    int id;
    int entry_time;
    int execution_time;
    int priority;
};

void generate_process(struct Process *process, int id) {
    process->id = id;
    process->entry_time = rand() % 10;
    process->execution_time = rand() % 10 + 1; // Ensure execution_time is at least 1
    process->priority = rand() % 5; // You can adjust the priority range as needed
}

int main() {
    srand(time(NULL));

    struct Process processes[NUM_PROCESSES];

    for (int i = 0; i < NUM_PROCESSES; i++) {
        generate_process(&processes[i], i + 1);
        printf("ID: %d, Entry Time: %d, Execution Time: %d, Priority: %d\n",
               processes[i].id, processes[i].entry_time, processes[i].execution_time, processes[i].priority);
    }

    return 0;
}
