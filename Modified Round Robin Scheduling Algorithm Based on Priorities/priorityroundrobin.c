#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

// Data Initialization
int temp, tempPID, ct[10], wt[10], tat[10], PIDIndex[10];
int n = 5; // dynamic number of processes
int BT[10] = {23, 19, 10, 11, 5}; // dynamic burst time for each process
int priority[10] = {4, 2, 1, 3, 5}; // dynamic priority level for each process
int timeQuantum_firsttime = 5; // inital time quantum
int cumulatedTime = 0;

typedef struct process_node {
    int burstTime;
    int originalBT;
    int priority;
    int waitingtime;
    int turnaroundtime;
    int indexCounter;
    int PID;
    struct process_node *next;
} PROCESS_NODE;

PROCESS_NODE *insertHead(PROCESS_NODE *head, PROCESS_NODE *new_node) {
    // link node & linked list together
    new_node->next = head;
    return new_node;
}

// populates data in the linked list
PROCESS_NODE populate_data(PROCESS_NODE **head) {
    // loops thru n number of times
    for (int i = 0; i < n; ++i) {
        // allocates memory space for new PROCESS_NODE
        PROCESS_NODE *new_node = (PROCESS_NODE *) malloc(sizeof(PROCESS_NODE));
        
        // assign burst time, priority, and process ID to each respective node
        new_node->burstTime = BT[i];
        new_node->originalBT = BT[i];
        new_node->priority = priority[i];
        new_node->waitingtime = 0;
        new_node->turnaroundtime = 0;
        new_node->PID = i + 1;
        new_node->next = NULL;
        
        // insert node into linked list
        *head = insertHead(*head, new_node);
    }
}

int get_priority_from_list(PROCESS_NODE *head) {
    PROCESS_NODE *temppNode = head;

    while (temppNode != NULL) {

        printf("Printing PLevel: %d\n", temppNode->priority);
        temppNode = temppNode->next;
    }
    return 1;
}

int get_burst_from_list(PROCESS_NODE *head) {
    PROCESS_NODE *temppNode = head;

    while (temppNode != NULL) {

        printf("Printing Burst time: %d\n", temppNode->burstTime);
        temppNode = temppNode->next;
    }
    return 1;
}

int get_TA_from_list(PROCESS_NODE *head) {
    PROCESS_NODE *temppNode = head;

    while (temppNode != NULL) {

        printf("Printing Waiting time time: %d\n", temppNode->waitingtime);
        temppNode = temppNode->next;
    }
    return 1;
}

int get_WT_from_list(PROCESS_NODE *head) {
    PROCESS_NODE *temppNode = head;
    while (temppNode != NULL) {
        printf("Printing Turnaround time: id: %d :  %d\n", temppNode->priority, temppNode->turnaroundtime);
        temppNode = temppNode->next;
    }
    return 1;
}

// print final results
int display_result(PROCESS_NODE *head) {
    PROCESS_NODE *temppNode = head;
    printf("Processes\tBurst Time\tWaiting Time\tTurnaround Time\n");
    float sumturnaround = 0;
    float sumwaiting = 0;
    
    // loop thru linked list
    while (temppNode != NULL) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", temppNode->PID, temppNode->originalBT, temppNode->waitingtime, temppNode->turnaroundtime);
        // add node's waiting time to total waiting time sum
        sumwaiting = sumwaiting + temppNode->waitingtime;
        // add node's turn around time to total turn around time sum
        sumturnaround = sumturnaround + temppNode->turnaroundtime;
        // point node to next node in the linked list
        temppNode = temppNode->next;
    }
    
    // average turnaround/waiting time is sum of all turnaround/waiting time divided by total number of processes in the beginning
    printf("Average Turnaround Time = %.2f\n", sumturnaround / (float) n);
    printf("Average Waiting Time = %.2f\n", sumwaiting / (float) n);
    return 1;
}

// return -1 when there is no process left
int calculate_dynamic_TQ(PROCESS_NODE *head) {
    int timeQuantum;
    int temparray[20];
    int evenOdd = 0;
    int arrayCounter = 0;
    PROCESS_NODE *temppNode = head;
    
    // allocate all remaining burst times to array
    while (temppNode != NULL) {
        if (temppNode->burstTime > 0) {
            evenOdd++;
            temparray[arrayCounter] = temppNode->burstTime;
            arrayCounter++;
        }
        // loop to next process node
        temppNode = temppNode->next;
    }
    // if there is no processs that is not complete yet, return -1 back to main to break the loop
    if (evenOdd == 0) {
        return -1;
    }
    
    // if there is only 1 process left, take its remaining burst time as the time quantum
    if (evenOdd == 1) {
        timeQuantum = temparray[0];
    }
    // if there is an even number of processes left, calculate new time quantum based on even formula
    else if (evenOdd % 2 == 0) {
        timeQuantum = (temparray[(evenOdd / 2)] + temparray[(evenOdd / 2) - 1]) / 2;
    }
    // else there is an odd number of processes left, calculate new time quantum absed on odd formula
    else {
        timeQuantum = temparray[(evenOdd + 1 / 2) - 1];
    }
    return timeQuantum;
}

// deducts burst time from the linked list
int deduct_burst_from_list(PROCESS_NODE **head, int deduction_amount) {
    PROCESS_NODE *temppNode = *head;
    int allCounter = 0;
    while (temppNode != NULL) {
        // if remaining burst time is is more than 0, run the process with time quantum given
        if (temppNode->burstTime > 0) {
            allCounter += 1;
            // if burstTime bigger than time quantum
            if (temppNode->burstTime > deduction_amount) {
                // cumulated time added with time quantum
                cumulatedTime = cumulatedTime + deduction_amount;
            }
            // if burstTime is smaller than time quantum
            else {
                // turn around time = cumulated time + remaining burst time
                temppNode->turnaroundtime = cumulatedTime + temppNode->burstTime;
                // waiting time = turn around time minus original burst time
                temppNode->waitingtime = temppNode->turnaroundtime - temppNode->originalBT;
                // cumulated time increased with remaining burst time
                cumulatedTime = cumulatedTime + temppNode->burstTime;
            }
            // deduct remaining burst time with current time quantum
            temppNode->burstTime = temppNode->burstTime - deduction_amount;
        }
        // loop to next process node
        temppNode = temppNode->next;
    }
    // if all the processes have remaining burst time of 0, return -1 to main
    if (allCounter == 0) {
        return -1;
    }
    // else return 0
    return 0;
}

// sort linked list by priority level
PROCESS_NODE *sort_linked_list_by_priority(PROCESS_NODE *head) {
    PROCESS_NODE *statichead = head;
    PROCESS_NODE *temppNode1counter = head;
    PROCESS_NODE *temppNode1 = head;
    PROCESS_NODE *temppNode2 = head;
    PROCESS_NODE *temppNodeCurrent = head;
    PROCESS_NODE *previous_node = temppNode2;

    // counting how many in list
    int count = 0;
    while (temppNode1counter != NULL) {
        count++;
        temppNode1counter = temppNode1counter->next;
    }

    // loop forever until all are sorted
    while (1) {
        
        // loop each iteration
        while (temppNode2->next != NULL) {

            // if current priority bigger than next, swap
            if (temppNode2->priority > temppNode2->next->priority) {

                // case when swapping first and second
                if (temppNode2 == previous_node) {
                    statichead = temppNode2->next;
                    temppNode2->next = previous_node->next->next;
                    statichead->next = temppNode2;
                }
                // else other case
                else {
                    previous_node->next = temppNode2->next;

                    // if swapping the last one
                    if (temppNode2->next->next == NULL) {
                        previous_node->next->next = temppNode2;
                        temppNode2->next = NULL;
                    }
                    // not swapping the last one
                    else {
                        temppNode2->next = temppNode2->next->next;
                        previous_node->next->next = temppNode2;
                    }
                }
                break;
            }
            // setting previous node
            previous_node = temppNode2;
            // setting tempnode to next
            temppNode2 = temppNode2->next;
        }
        // reset all temp data for next loop
        previous_node = statichead;
        temppNode2 = statichead;

        // temp data
        int boolbreak = 0;

        // if all is sorted, the count will remain 0
        while (temppNode1->next != NULL) {
            if (temppNode1->priority > temppNode1->next->priority) {
                boolbreak++;
            }
            temppNode1 = temppNode1->next;
        }
        temppNode1 = statichead;
        // if count is 0, break
        if (boolbreak == 0) {
            break;
        }
    }
    printf("Number of Processes = %d\n", count);
    return statichead;
}

// sort linked list by PROCESS ID
PROCESS_NODE *sort_linked_list_by_PID(PROCESS_NODE *head) {
    PROCESS_NODE *statichead = head;
    PROCESS_NODE *temppNode1counter = head;
    PROCESS_NODE *temppNode1 = head;
    PROCESS_NODE *temppNode2 = head;
    PROCESS_NODE *temppNodeCurrent = head;
    PROCESS_NODE *previous_node = temppNode2;

    // counting how many in list
    int count = 0;
    while (temppNode1counter != NULL) {
        count++;
        temppNode1counter = temppNode1counter->next;
    }

    // loop forever until all are sorted
    while (1) {

        // loop each iteration
        while (temppNode2->next != NULL) {

            // if current bigger than next, swap
            if (temppNode2->PID > temppNode2->next->PID) {

                // case when swapping first and second
                if (temppNode2 == previous_node) {

                    statichead = temppNode2->next;
                    temppNode2->next = previous_node->next->next;
                    statichead->next = temppNode2;

                    // else other case
                } else {

                    previous_node->next = temppNode2->next;

                    // if swapping the last one
                    if (temppNode2->next->next == NULL) {
                        previous_node->next->next = temppNode2;
                        temppNode2->next = NULL;

                        // not swapping the last one
                    } else {
                        temppNode2->next = temppNode2->next->next;
                        previous_node->next->next = temppNode2;
                    }
                }
                break;
            }
            // setting previous node
            // setting tempnode to next
            previous_node = temppNode2;
            temppNode2 = temppNode2->next;
        }
        // reset all temp data for next loop
        previous_node = statichead;
        temppNode2 = statichead;

        // temp data
        int boolbreak = 0;

        // if all is sorted, the count will remain 0
        while (temppNode1->next != NULL) {
            if (temppNode1->PID > temppNode1->next->PID) {
                boolbreak++;
            }
            temppNode1 = temppNode1->next;
        }
        temppNode1 = statichead;
        // if count is 0, break
        if (boolbreak == 0) {
            break;
        }
    }
    printf("Number of Processes = %d\n", count);
    return statichead;
}

// sort linked list by shortest burst time first
PROCESS_NODE *sort_linked_list_by_bursttime(PROCESS_NODE *head) {
    PROCESS_NODE *statichead = head;
    PROCESS_NODE *temppNode1counter = head;
    PROCESS_NODE *temppNode1 = head;
    PROCESS_NODE *temppNode2 = head;
    PROCESS_NODE *temppNodeCurrent = head;
    PROCESS_NODE *previous_node = temppNode2;
    
    // counting how many in list
    int count = 0;
    while (temppNode1counter != NULL) {
        count++;
        temppNode1counter = temppNode1counter->next;
    }
    
    // loop forever until all are sorted
    while (1) {
        
        // loop each iteration
        while (temppNode2->next != NULL) {
            
            // if current burst time bigger than next, swap
            if (temppNode2->burstTime > temppNode2->next->burstTime) {
                
                // case when swapping first and second
                if (temppNode2 == previous_node) {
                    statichead = temppNode2->next;
                    temppNode2->next = previous_node->next->next;
                    statichead->next = temppNode2;
                }
                // else other case
                else {
                    previous_node->next = temppNode2->next;
                    
                    // if swapping the last one
                    if (temppNode2->next->next == NULL) {
                        previous_node->next->next = temppNode2;
                        temppNode2->next = NULL;
                    }
                    // not swapping the last one
                    else {
                        temppNode2->next = temppNode2->next->next;
                        previous_node->next->next = temppNode2;
                    }
                }
                break;
            }
            // setting previous node
            previous_node = temppNode2;
            // setting tempnode to next
            temppNode2 = temppNode2->next;

        }
        // reset all temp data for next loop
        previous_node = statichead;
        temppNode2 = statichead;

        // temp data
        int boolbreak = 0;
        
        // if all is sorted, the count will remain 0
        while (temppNode1->next != NULL) {
            if (temppNode1->burstTime > temppNode1->next->burstTime) {
                boolbreak++;
            }
            temppNode1 = temppNode1->next;
        }
        temppNode1 = statichead;
        // if count is 0, break
        if (boolbreak == 0) {
            break;
        }
    }
    return statichead;
}

int main() {
    //create linked list head
    PROCESS_NODE *head = NULL;
    
    // populate linked list with given burst times & priority numbers
    populate_data(&head);
    
    // sort linked list based on priority level
    head = sort_linked_list_by_priority(head);
    
    printf("Time slice = %d\n", timeQuantum_firsttime);
    
    // do 1 round robin cycle on the linked list
    deduct_burst_from_list(&head, timeQuantum_firsttime);


    int notComplete_TQ = 0;
    // loop forever
    while (1) {
        // sort linked list based on burst time
        head = sort_linked_list_by_bursttime(head);
        
        // calculate new time quantum
        notComplete_TQ = calculate_dynamic_TQ(head);
        
        // if time quantum is -1, means there is no more processes needed to run, break the while loop
        if (notComplete_TQ == -1) {
            break;
        }
        // else, do 1 round robin cycle on the sorted linked list based on burst time
        deduct_burst_from_list(&head, notComplete_TQ);
    }
    
    // sort the linked list by PID to print anmd display final result
    head = sort_linked_list_by_PID(head);
    // print final results
    display_result(head);
}