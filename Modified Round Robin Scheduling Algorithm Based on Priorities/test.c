#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

// Data
int temp, tempPID, ct[10], wt[10], tat[10], PIDIndex[10];
int n = 5; // dynamic number of processor
int BT[10] = {23, 19, 10, 11, 5}; // dynamic burst time for each process
int priority[10] = {4, 2, 1, 3, 5};


typedef struct process_node {
    int burstTime;
    int priority;
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

        printf("Printing BT: %d\n", temppNode->priority);
        temppNode = temppNode->next;
    }
    return 1;
}

int sort_linked_list_by_priority(PROCESS_NODE *head) {
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

            if (temppNode2->priority < temppNode2->next->priority) {

                previous_node->next = temppNode2->next;

                if (temppNode2->next->next == NULL) {
                    previous_node->next->next = temppNode2;
                    temppNode2->next = NULL;
                } else {
                    temppNode2->next = temppNode2->next->next;
                    previous_node->next->next = temppNode2;
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
            if (temppNode1->priority > temppNode1->next->priority) {
                boolbreak++;
            }
            temppNode1 = temppNode1->next;
        }
        if (boolbreak == 0) {
            break;
        }

    }




    printf("Count:%d\n", count);
    return 1;


}


PROCESS_NODE sort_linked_list_by_burst(PROCESS_NODE *head) {
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

            if (temppNode2->burstTime < temppNode2->next->burstTime) {

                previous_node->next = temppNode2->next;

                if (temppNode2->next->next == NULL) {
                    previous_node->next->next = temppNode2;
                    temppNode2->next = NULL;
                } else {
                    temppNode2->next = temppNode2->next->next;
                    previous_node->next->next = temppNode2;
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
    sort_linked_list_by_burst(head)


}