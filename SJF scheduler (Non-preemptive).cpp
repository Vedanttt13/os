#include <stdio.h>
#include <limits.h>

struct Process {
    int pid;
    int burst_time;
    int arrival_time;
    int waiting_time;
    int turnaround_time;
    int completed;
};

int findNextProcess(struct Process proc[], int n, int current_time) {
    int shortest_idx = -1;
    int min_burst_time = INT_MAX;
    
    for (int i = 0; i < n; i++) {
        if (proc[i].arrival_time <= current_time && proc[i].completed == 0 && proc[i].burst_time < min_burst_time) {
            min_burst_time = proc[i].burst_time;
            shortest_idx = i;
        }
    }
    
    return shortest_idx;
}

void findWaitingAndTurnaroundTime(struct Process proc[], int n, float* avg_wt, float* avg_tat) {
    int current_time = 0;
    int completed_processes = 0;
    int total_waiting_time = 0, total_turnaround_time = 0;

    while (completed_processes < n) {
        int idx = findNextProcess(proc, n, current_time);
        
        if (idx != -1) {
            proc[idx].waiting_time = current_time - proc[idx].arrival_time;
            if (proc[idx].waiting_time < 0) proc[idx].waiting_time = 0;
            
            current_time += proc[idx].burst_time;
            proc[idx].turnaround_time = proc[idx].waiting_time + proc[idx].burst_time;
            proc[idx].completed = 1;
            completed_processes++;
            
            total_waiting_time += proc[idx].waiting_time;
            total_turnaround_time += proc[idx].turnaround_time;
        } else {
            current_time++;
        }
    }

    *avg_wt = (float)total_waiting_time / n;
    *avg_tat = (float)total_turnaround_time / n;
}

void SJF(struct Process proc[], int n) {
    float avg_wt = 0.0, avg_tat = 0.0;
    findWaitingAndTurnaroundTime(proc, n, &avg_wt, &avg_tat);

    printf("ProcessID\tArrivalTime\tBurstTime\tWaitingTime\tTurnaroundTime\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].arrival_time, proc[i].burst_time,
            proc[i].waiting_time, proc[i].turnaround_time);
    }

    printf("\nAverage Waiting Time: %.2f\n", avg_wt);
    printf("Average Turnaround Time: %.2f\n", avg_tat);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter arrival time and burst time for process %d: ", proc[i].pid);
        scanf("%d %d", &proc[i].arrival_time, &proc[i].burst_time);
        proc[i].completed = 0;
    }

    SJF(proc, n);

    return 0;
}

/*Enter number of processes: 3
Enter arrival time and burst time for process 1: 0 4
Enter arrival time and burst time for process 2: 1 2
Enter arrival time and burst time for process 3: 2 1
*/

