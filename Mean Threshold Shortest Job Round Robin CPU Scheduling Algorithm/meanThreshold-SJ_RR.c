#include <stdio.h>

int main(){
    // Data
    int n = 6; // number of processor
    int BT[10] = {5,6,7,9,2,3}; // burst time for each process
    int TQ = 3; // time quantum value

    // init variables
    int sum = 0;
    int counts = 0;
    int countr = 0;

    // calculate sum of all burst time
    for (int i = 0; i < n; ++i) {
        sum += BT[i];
    }

    // getting average of the burst time, which is also the threshold value
    int thresholdValue = sum/n;


    return 0;

}


