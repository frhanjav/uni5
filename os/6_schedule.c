// Using the following processes (with burst time given in brackets) P(8), Q(13), R(10), S(12) and T(15) have arrived at the same time. Write a C codes to depict their completion, turnaround and waiting time in tabular form when the processes are scheduled using 
    // FCFS method.
    // SJF method.
    // Round Robin method with the time quantum of 3 units.

    #include <stdio.h>

    #define NUM_PROCESSES 5

    typedef struct Process {
        int p_num;
        int at,   // Arrival time
            bt,   // Burst time
            ct,   // Completion time
            tat,  // Turnaround time
            wt;   // Waiting time
        int done;
        } Process;

    void initProc(Process processes[], int BT[], int AT[], int n) {
        for (int i = 0; i < n; i++) {
            processes[i].p_num = i + 1;
            processes[i].at = AT[i];
            processes[i].bt = BT[i];
            processes[i].ct = 0;
            processes[i].tat = 0;
            processes[i].wt = 0;
            processes[i].done = 0;

            }
        }

    void printProc(Process processes[], int n) {
        for (int i = 0; i < n; i++) {
            printf("%d, %d, %d, %d, %d, %d\n",
                processes[i].p_num, processes[i].at, processes[i].bt,
                processes[i].ct, processes[i].tat, processes[i].wt);
            }
        }

    void sortArrivalTime(Process processes[], int n) {
        for (int i = 0; i < n - 1; i++) {
            int minIdx = i;
            for (int j = i + 1; j < n; j++) {
                if (processes[j].at < processes[minIdx].at) {
                    minIdx = j;
                    }
                }

            if (minIdx != i) {
                Process temp = processes[i];
                processes[i] = processes[minIdx];
                processes[minIdx] = temp;
                }
            }
        }

    void sortBurstTime(Process processes[], int n) {
        for (int i = 0; i < n - 1; i++) {
            int minIdx = i;
            for (int j = i + 1; j < n; j++) {
                if (processes[j].bt < processes[minIdx].bt) {
                    minIdx = j;
                    }
                }

            if (minIdx != i) {
                Process temp = processes[i];
                processes[i] = processes[minIdx];
                processes[minIdx] = temp;
                }
            }
        }

    void FCFS(Process processes[], int n) {
        sortArrivalTime(processes, n);
        // assuming already sorted in PID order
        int t_stamp = 0;
        for (int i = 0; i < n; i++) {
            processes[i].ct = processes[i].bt + t_stamp;  // update compltion time

            processes[i].tat = processes[i].ct - processes[i].at;  // update Turnarround time
            processes[i].wt = t_stamp - processes[i].at;           // update Turnarround time

            t_stamp = processes[i].ct;
            }
        }

    void SJF(Process processes[], int n) {
        sortArrivalTime(processes, n);

        int t_stamp = 0;
        int done = 0;

        while (done < n) {
            int sel_proc = -1;
            int min_bt = 9999;

            // search for next shortest job that is not Done
            for (int i = 0; i < n; i++) {
                if (processes[i].at <= t_stamp && !processes[i].done) {
                    if (processes[i].bt < min_bt) {
                        min_bt = processes[i].bt;
                        sel_proc = i;
                        }
                    }
                }

            // processes selected
            if (sel_proc != -1) {
                processes[sel_proc].ct = t_stamp + processes[sel_proc].bt; // ct
                processes[sel_proc].tat = processes[sel_proc].ct - processes[sel_proc].at; // tat 
                processes[sel_proc].wt = processes[sel_proc].tat - processes[sel_proc].bt; // wt
                processes[sel_proc].done = 1; // mark done

                t_stamp += processes[sel_proc].bt;
                done++;
                }
            else {
                t_stamp++;
                }
            }
        }

    void RR(Process processes[], int n, int time_quantum) {
        int t_stamp = 0;
        int done = 0;
        int remaining_bt[n];

        // Initialize remaining burst times
        for (int i = 0; i < n; i++) {
            remaining_bt[i] = processes[i].bt;
            }

        while (done < n) {
            for (int i = 0; i < n; i++) {
                if (remaining_bt[i] > 0 && processes[i].at <= t_stamp) {
                    if (remaining_bt[i] <= time_quantum) {
                        t_stamp += remaining_bt[i];
                        processes[i].ct = t_stamp;
                        processes[i].tat = processes[i].ct - processes[i].at;
                        processes[i].wt = processes[i].tat - processes[i].bt;
                        remaining_bt[i] = 0;
                        done++;
                        }
                    else {
                        t_stamp += time_quantum;
                        remaining_bt[i] -= time_quantum;
                        }
                    }
                }
            // If no process is ready, increment the timestamp
            if (done < n && t_stamp < processes[done].at) {
                t_stamp++;
                }
            }
        }

    void SRTF(Process processes[], int n) {
        int t_stamp = 0;
        int done = 0;
        int remaining_bt[n];

        // Initialize remaining burst times
        for (int i = 0; i < n; i++) {
            remaining_bt[i] = processes[i].bt;
            }

        while (done < n) {
            int sel_proc = -1;
            int min_bt = 9999;

            // Find the process with the shortest remaining burst time
            for (int i = 0; i < n; i++) {
                if (processes[i].at <= t_stamp && remaining_bt[i] > 0 && remaining_bt[i] < min_bt) {
                    sel_proc = i;
                    min_bt = remaining_bt[i];
                    }
                }

            if (sel_proc != -1) {
                t_stamp++;
                remaining_bt[sel_proc]--;

                // If process finishes
                if (remaining_bt[sel_proc] == 0) {
                    processes[sel_proc].ct = t_stamp;
                    processes[sel_proc].tat = processes[sel_proc].ct - processes[sel_proc].at;
                    processes[sel_proc].wt = processes[sel_proc].tat - processes[sel_proc].bt;
                    done++;
                    }
                }
            else {
                t_stamp++; // No process available; increment time
                }
            }
        }

    void HRRN(Process processes[], int n) {
        int t_stamp = 0;
        int done = 0;

        while (done < n) {
            int sel_proc = -1;
            float max_rr = -1.0; // Response Ratio = (waiting time + burst time) / burst time

            for (int i = 0; i < n; i++) {
                if (!processes[i].done && processes[i].at <= t_stamp) {
                    float rr = (float)(t_stamp - processes[i].at + processes[i].bt) / processes[i].bt;
                    if (rr > max_rr) {
                        max_rr = rr;
                        sel_proc = i;
                        }
                    }
                }

            if (sel_proc != -1) {
                processes[sel_proc].ct = t_stamp + processes[sel_proc].bt;
                processes[sel_proc].tat = processes[sel_proc].ct - processes[sel_proc].at;
                processes[sel_proc].wt = processes[sel_proc].tat - processes[sel_proc].bt;
                processes[sel_proc].done = 1;

                t_stamp = processes[sel_proc].ct;
                done++;
                }
            else {
                t_stamp++; // No process available; increment time
                }
            }
        }


    int main() {
        Process processes[NUM_PROCESSES];
        int BT[NUM_PROCESSES] = { 5, 6, 6, 7, 4 };  // Burst times for the processes
        int AT[NUM_PROCESSES] = {0, 2, 3, 2, 5};  // Burst times for the processes
        // int AT[NUM_PROCESSES] = { 0, 0, 0, 0, 0 };  // Burst times for the processes

        printf("\n");
        printf("Init Processes \n");
        initProc(processes, BT, AT, NUM_PROCESSES);

        printf("FCFS Solution \n");
        printf("No|AT|BT|CT|TAT|WT\n");
        initProc(processes, BT, AT, NUM_PROCESSES);
        FCFS(processes, NUM_PROCESSES);
        printProc(processes, NUM_PROCESSES);
        printf("\n");

        printf("SJF Solution \n");
        printf("No|AT|BT|CT|TAT|WT\n");
        initProc(processes, BT, AT, NUM_PROCESSES);
        SJF(processes, NUM_PROCESSES);
        printProc(processes, NUM_PROCESSES);
        printf("\n");

        printf("RR Solution \n");
        printf("No|AT|BT|CT|TAT|WT\n");
        initProc(processes, BT, AT, NUM_PROCESSES); // Reinitialize processes
        RR(processes, NUM_PROCESSES, 3); // Example time quantum = 3
        printProc(processes, NUM_PROCESSES);
        printf("\n");

        printf("SRTF Solution \n");
        printf("No|AT|BT|CT|TAT|WT\n");
        initProc(processes, BT, AT, NUM_PROCESSES); // Reinitialize processes
        SRTF(processes, NUM_PROCESSES);
        printProc(processes, NUM_PROCESSES);
        printf("\n");

        printf("HRRN Solution \n");
        printf("No|AT|BT|CT|TAT|WT\n");
        initProc(processes, BT, AT, NUM_PROCESSES); // Reinitialize processes
        HRRN(processes, NUM_PROCESSES);
        printProc(processes, NUM_PROCESSES);
        printf("\n");

        return 0;
    }