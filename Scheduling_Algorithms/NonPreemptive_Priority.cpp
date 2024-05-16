#include <stdio.h>
#include <stdlib.h>

// Process structure
struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
};

// Function to compare processes by priority for qsort
int compareByPriority(const void* a, const void* b) {
    const struct Process* p1 = (const struct Process*)a;
    const struct Process* p2 = (const struct Process*)b;
    return p1->burst_time - p2->burst_time;
}

// Non-preemptive Priority scheduling function
void nonPreemptivePriority(struct Process* processes, int n) {
    // Sort processes by priority (burst time)
    qsort(processes, n, sizeof(struct Process), compareByPriority);

    int current_time = 0;

    printf("Order of execution: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", processes[i].id);
        current_time += processes[i].burst_time;
    }
    printf("\n");
}

int main() {
    struct Process processes[] = {
        {1, 0, 6, 6},
        {2, 1, 8, 8},
        {3, 2, 7, 7},
        {4, 3, 3, 3}
    };
    int n = sizeof(processes) / sizeof(processes[0]);

    nonPreemptivePriority(processes, n);

    return 0;
}
