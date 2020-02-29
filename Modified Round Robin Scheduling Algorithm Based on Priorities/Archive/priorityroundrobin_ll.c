#include <stdio.h>

typedef struct node_struct {
    int pid;
    int pnum;
    int btime;
    int btime_left;
    int wtime;
    int tatime;
    struct node_struct *next;
}   Process;

Node *create_node(int *pid, int *pnum, int *btime);
Node *insert_node_priority(Node *head, Node *new_node);
Node *insert_node_bursttime(Node *head);
Node *print_list(Node *head, const char *text);
Node *free_list(Node *head);
Node *do_burst(Node *head, int *t);
int *count_process(Node *head);

int main()
{
    /*
    * 	i, j  -  for loop counters
    * 	n -  number of processes
    *	bu[] - 	remaining burst time array for each process
    *	wa[] - 	waiting time array
    *	tat[] -  turn around time array
    *	t -  time slice/quantum
    *	ct[] - 	burst time array for each process
    *	max - to store biggest burst time
    * 	awt - average waiting time
    *	att - average turn around time
    *	temp - 	temporary variable
    */
    int i, j, n, k, bu[20], wa[20], tat[20], t, ct[20], max, pl[20], a, pn[20], b, temp_array[20], total_processes, r;
    float awt=0, att=0, temporary=0;

    Node *head = NULL;
    Node *new_node;
    Node *temp;

    int iBurstTime[20] = {23, 19, 10, 11, 5};
    int priority_array[20] = {4, 2, 1, 3, 5};
    t = 5;


    for(i=0;i<20;i++) {
        if(iBurstTime[i]!=0) {
            new_node = create_node(i+1, priority_array[i], iBurstTime[i]);

            head = insert_node_priority(head, new_node);
        }
    }

    head = do_burst(head, t);
    temp = head;
    
    while (temp->btime_left != 0) {
        head = insert_node_bursttime(temp, temp->next);
        temp = temp->next;
    }
   
    return 0;
}

Node *create_node(int *pid, int *pnum, int *btime) {
	Node *new_node = (Node *)malloc(sizeof(Node));
	if (new_node != NULL) {
		new_node->pid = pid;
        new_node->pnum = pnum;
        new_node->btime = btime;
        new_mode->btime_left = btime;
        new_node->wtime = 0;
        new_node->tatime = 0;
		new_node->next = NULL;
	}
	return new_node;
}

Node *insert_node_priority(Node *head, Node *new_node) {
    if (head == NULL) {
        return new_node;
    }
    else if (head->next == NULL) {
        if (head->pnum > new_node->pnum) {
            head->next = new_node;
            return head;  
        }
        else {
            new_node->next = head;
            return new_node;
        }

    }
    else if (head->next != NULL) {
        Node *temp = head;
        while (temp->next != NULL) {
            //pnum bigger
            if (new_node->pnum > temp->pnum) {
                temp = temp->next;
            }
            //pnum smaller
            else if (new_node->pnum < temp->pnum) {
                new_node->next = temp;
                //current pos is head
                if (temp == head) {
                    return new_node;
                }
                //current pos is NOT head
                else {
                    Node *prev_node = head;
                    while (prev_node->next != temp) {
                        prev_node = prev_node->next;
                    }
                    prev_node->next = new_node;
                    return head;
                }
            }
        }
        
        // last temp
        if (temp->next == NULL && new_node->pnum > temp->pnum) {
            temp->next = new_node;
            return head;
        }
    }
}

Node *insert_node_bursttime(Node *head) {
    
}

Node *free_list(Node *head) {
	Node *temp = head;
	// loops thru linked list, frees every node struture
	while (temp != NULL) {
		temp = temp->next;
		free(head);
		head = temp;
	}
	return NULL;
}

Node *print_list(Node *head, const char *text, total_processes {
    float twt=0, ttt=0;
    printf("%s", text);
    Node *temp = head;
    while (temp != NULL) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", temp->pid, temp->btime, temp->wtime, temp->tatime);
        twt+=temp->wtime;
        ttt+=temp->tatime;
    }
    
    printf("\nAverage Waiting Time:\t\t%.3f\n", twt/total_processes);
    printf("Average Turn Around Time:\t%.3f\n", ttt/total_processes);
}
                 
Node *do_burst(Node *head. int *t) {
    Node *temp = head;
    while (temp != NULL) {
        if(temp->btime_left < t) {
            temp->tatime = temporary + temp->btime_left;
            temp->wtime = temp->tatime - temp->btime;
            temporary = temporary + temp->btime_left;
            temp->btime_left = 0;
        }
        else {
            temp->btime_left = temp->btime_left - t;
            temporary = temporary + t;
        }
        
        temp = temp->next;
    }
    
    return head;
}
                 
int *count_process(Node *head) {
    int counter = 0;
    Node *temp = head;
    while (temp->next != NULL) {
        counter = counter + 1;
        temp = temp->next;
    }
    
    return counter;
}