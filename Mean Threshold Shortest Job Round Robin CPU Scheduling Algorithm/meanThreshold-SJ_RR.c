#include <stdio.h>


int main() {

    // Data
    int temp, tempPID, ct[10], wt[10], tat[10], PIDIndex[10];
    int n = 6; // number of processor
    int BT[10] = {5, 6, 7, 9, 2, 3}; // burst time for each process
    int PID[10];
    int TQ = 3; // time quantum value

    // init variables
    int sum = 0;
    int counts = 0;
    int countr = 0;
    int cumulatedtime = 0;
    float totalTurnaround = 0;
    float totalWaitingTime = 0;

    // auto populate PID
    for (int i1 = 0; i1 < n; ++i1) {
        PID[i1] = i1;
    }

    // sorting in ascending order
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (BT[i] > BT[j]) {

                // sorting the burst time; BT[]
                temp = BT[i];
                BT[i] = BT[j];
                BT[j] = temp;


                // Sorting the Process ID, so the PID do not get lost
                tempPID = PID[i];
                PID[i] = PID[j];
                PID[j] = tempPID;
            }
        }
    }

    // cloning BT array
    for (int l = 0; l < n; ++l) {
        ct[l] = BT[l];
        sum += BT[l]; //sum
    }

    // calculating threshold
    int thresholdValue = sum / n;

    if (n > 0) {
        for (int eachProcess = 0; eachProcess < n; ++eachProcess) {

            // count = no. of process is less than the threshold value
            if (BT[eachProcess] <= thresholdValue) {
                counts = counts + 1;
            } else {
                // countr = no. of process that is above the threshold value
                countr = countr + 1;
            }
        }

        // FCFS will be applied
        // first process waiting time is 0

        for (int j = 0; j <= counts - 1; ++j) {
            // waiting times
            wt[j] = cumulatedtime;
            cumulatedtime = cumulatedtime + BT[j];
            // turnaround time
            tat[j] = cumulatedtime;
        }
        // RRA
        // loop the max number of the slice for the largest burst time process

        for (int rraindex = 0; rraindex < (ct[n - 1] / TQ) + 1; ++rraindex) {

            // loop the number of process left
            for (int i = counts; i < n; ++i) {
                if (BT[i] != 0) {
                    if (BT[i] <= TQ) {
                        tat[i] = cumulatedtime + BT[i];
                        wt[i] = tat[i] - ct[i];
                        cumulatedtime = cumulatedtime + BT[i];
                        BT[i] = 0;
                    } else {
                        BT[i] = BT[i] - TQ;
                        cumulatedtime = cumulatedtime + TQ;
                    }
                }
            }
        }
    }

    printf("Number of Processes = %d\n", n);
    printf("Time Slice = %d\n", TQ);
    printf("Processes\tBurst Time\tWaiting Time\tTurnaround Time\n");

    //sorting ascending by pid
    for (int m = 0; m < n; ++m) {
        PIDIndex[PID[m]] = m;
    }

    for (int k = 0; k < n; ++k) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", k+1, ct[PIDIndex[k]], wt[PIDIndex[k]], tat[PIDIndex[k]]);
        totalTurnaround += (float) tat[PIDIndex[k]];
        totalWaitingTime += (float) wt[PIDIndex[k]];
    }
    printf("Average Turnaround Time = %.2f\n", totalTurnaround / (float) n);
    printf("Average Waiting Time = %.2f\n", totalWaitingTime / (float) n);


}