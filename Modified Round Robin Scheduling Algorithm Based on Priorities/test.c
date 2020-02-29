#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

// Data
int temp, tempPID, ct[10], wt[10], tat[10], PIDIndex[10];
int n = 5; // dynamic number of processor
int BT[10] = {23, 19, 10, 11, 5}; // dynamic burst time for each process
int priority[10] = {4, 2, 1, 3, 5};
int timeQuantum_firsttime = 5;
//int priority[10] = {4, 2, 3, 5, 1};


typedef struct process_node {
    int burstTime;
    int priority;
    int waitingtime;
    int turnaroundtime;
    struct process_node *next;
} PROCESS_NODE;

PROCESS_NODE *insertHead(PROCESS_NODE *head, PROCESS_NODE *new_node) {
    new_node->next = head;
    return new_node;
}


PROCESS_NODE populate_data(PROCESS_NODE **head) {

    for (int i = 0; i < n; ++i) {


        PROCESS_NODE *new_node = (PROCESS_NODE *) malloc(sizeof(PROCESS_NODE));
        new_node->burstTime = BT[i];
        new_node->priority = priority[i];
        new_node->next = NULL;
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

void deduct_burst_from_list(PROCESS_NODE *head,int deduction_amount){
    PROCESS_NODE *temppNode = head;

    int cumulatedTime = 0;
    while (temppNode != NULL) {

        printf("Printing Burst time: %d\n", temppNode->burstTime);
        if(temppNode->burstTime>deduction_amount){
            temppNode->burstTime =  temppNode->burstTime-deduction_amount;

        }



        temppNode = temppNode->next;
    }

}

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

            // if current bigger than next, swap
            if (temppNode2->priority > temppNode2->next->priority) {

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


    printf("Count:%d\n", count);
    return statichead;


}


PROCESS_NODE *sort_linked_list_by_bursttime(PROCESS_NODE *head) {
    PROCESS_NODE *statichead = head;
    PROCESS_NODE *temppNode1counter = head;
    PROCESS_NODE *temppNode1 = head;
    PROCESS_NODE *temppNode2 = head;
    PROCESS_NODE *temppNodeCurrent = head;
    PROCESS_NODE *previous_node = temppNode2;
    int count = 0;
    while (temppNode1counter != NULL) {

        count++;
        temppNode1counter = temppNode1counter->next;
    }

    while (1) {
        while (temppNode2->next != NULL) {

            if (temppNode2->burstTime > temppNode2->next->burstTime) {
                if (temppNode2 == previous_node) {

                    statichead = temppNode2->next;
                    temppNode2->next = previous_node->next->next;
                    statichead->next = temppNode2;


                } else {

                    previous_node->next = temppNode2->next;

                    if (temppNode2->next->next == NULL) {
                        previous_node->next->next = temppNode2;
                        temppNode2->next = NULL;
                    } else {
                        temppNode2->next = temppNode2->next->next;
                        previous_node->next->next = temppNode2;
                    }

                }
                break;
            }

            previous_node = temppNode2;
            temppNode2 = temppNode2->next;

        }
        previous_node = statichead;
        temppNode2 = statichead;


        int boolbreak = 0;

        while (temppNode1->next != NULL) {
            if (temppNode1->burstTime > temppNode1->next->burstTime) {
                boolbreak++;
            }
            temppNode1 = temppNode1->next;
        }
        temppNode1 = statichead;

        if (boolbreak == 0) {
            break;
        }

    }


    printf("Count:%d\n", count);
    return statichead;


}

int main() {
    PROCESS_NODE *head = NULL;
    populate_data(&head);

    head = sort_linked_list_by_priority(head);
    deduct_burst_from_list(head,timeQuantum_firsttime);
    get_priority_from_list(head);


    head = sort_linked_list_by_bursttime(head);
    get_burst_from_list(head);


}