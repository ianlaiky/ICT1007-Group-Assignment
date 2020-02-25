#include <stdio.h>

typedef struct node_struct {
    int pid;
    int pnum;
    int btime;
    int wtime;
    int tatime;
    struct node_struct *next;
}   Process;

Node *create_node(int *pid, int *pnum, int *btime);
Node *insert_node(Node *head, Node *new_node);
Node *print_list(Node *head, const char *text);
Node *free_list(Node *head);
bool *check_word(char *word);

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
        float awt=0, att=0, temp=0;
        n = 0;
        b = 0;
        r = 0;
        
        Node *head = NULL;
        Node *new_node;
        Node *temp;
        
        int iBurstTime[20] = {23, 19, 10, 11, 5};
        int priority_array[20] = {4, 2, 1, 3, 5};
        t = 5;

        for(i=0;i<20;i++)
        {
                if(iBurstTime[i]!=0)
                {
                        bu[i] = iBurstTime[i];
                        pn[i] = i+1;
                        n=n+1;
                }
        }
        total_processes = n;
        printf("Number of Processes = %d\n", n);
        printf("Time Slice = %d\n", t);

        //Indexing algo    
        for(i=0;i<20;i++) 
        {
                if(iBurstTime[i]!=0)
                {
                        temp_array[priority_array[i]-1] = iBurstTime[i];
                        pl[priority_array[i]-1] = pn[i];
                }
        }

        for (i = 0; i <20; i++)
        {
                if(iBurstTime[i]!=0 && priority_array[i]!=0)
                {
                        iBurstTime[i] = temp_array[i];
                        priority_array[i] = i+1;
                        pn[i] = pl[i];
                }
        }

        for(j=0;j<20;j++)
        {
                printf("\nCycle #%d:\n", j+1);
                printf("Processes Left: %d\n", n);
                for(i=0;i<n;i++)
                {
                        printf("%d ", iBurstTime[i]);
                }
                printf("\n");
                for(i=0;i<n;i++)
                {
                        printf("%d ", pn[i]);
                }
                printf("\n");
                //if first process in queue is completed, burst time is 0.
                if(iBurstTime[0]==0)
                {
                        break;
                }

                // Loop each process
                for(i=0; i<n; i++)
                {
                        // If bu[i] time lesser than or equal to time slice/quantum,
                        if(iBurstTime[i]<=t)
                        {
                                r = pn[i];
                                // Add to temp & turn around time array.
                                tat[r-1]=temp+iBurstTime[i];
                                temp=temp+iBurstTime[i];
                                // Set time left to complete process to 0.
                                iBurstTime[i]=0;
                                b=b+1;
                        }
                        else
                        {
                                // Deduct time slice/quantum from remaining burst time for current process.
                                iBurstTime[i]=iBurstTime[i]-t;
                                // Increment temp by t
                                temp=temp+t;
                        }
                }
                
                //Reorder based on SJF
                for(i=0;i<n;i++)
                {
                        for(k=i+1;k<n;k++)
                        {
                                if(iBurstTime[i]==0)
                                {
                                        iBurstTime[i] = iBurstTime[k];
                                        iBurstTime[k] = 0;
                                        continue;
                                }                    
                                else if(iBurstTime[i]>iBurstTime[k] && iBurstTime[k]!=0)
                                {
                                        a = iBurstTime[i];
                                        iBurstTime[i] = iBurstTime[k];
                                        iBurstTime[k] = a;
                                    
                                        a = pn[i];
                                        pn[i] =  pn[k];
                                        pn[k] = a;
                                }
                        }
                }
                
                n=n-b;
                b=0;
                //Calculate new dynamic time quantum
                if(n%2==0)
                {
                        //int test = (n/2)-1;
                        //int test1= (n/2);
                        //t=(iBurstTime[(n/2)-1]+iBurstTime[n/2])/2;
                        t=(iBurstTime[(n/2)-1]+iBurstTime[(n/2)])/2;
                }
                else
                {
                        //int test2 = ((n+1)/2)-1;
                        t=iBurstTime[((n+1)/2)-1];
                }

                printf("\nNew Dynamic Time Slice: %d\n", t);
                printf("Reordered Array\n");
                for(i=0;i<20;i++)
                {
                        printf("%d ", iBurstTime[i]);
                }
        }

        // ** Calculate and print the 'waiting time' and 'turn-around-time' for each process. **
        printf("\nPROCESS\t\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n");
        for(i=0; i<total_processes; i++)
        {
                r = pn[i];
                printf("%d, %d\n", pn[i], tat[i]);
                // Turn Around Time - burst Time  = Waiting Time
                wa[i] = tat[i] - bu[r-1];
                printf("%d\t\t%d\t\t%d\t\t%d\n", i+1, bu[i], wa[i], tat[i]);

                // Getting Total Waiting & Turn Around Time
                awt += wa[i];
                att += tat[i];
        }

        // Calculate Average Waiting & Turn Around Time
        printf("\nAverage Waiting Time:\t\t%.3f\n", awt/total_processes);
        printf("Average Turn Around Time:\t%.3f\n", att/total_processes);

        return 0;
}

Node *create_node(int *pid, int *pnum, int *btime) {
	Node *new_node = (Node *)malloc(sizeof(Node));
	if (new_node != NULL) {
		new_node->pid = pid;
        new_node->pnum = pnum;
        new_node->pnum = pnum;
		new_node->next = NULL;
	}
	return new_node;
}

Node *insert_node(Node *head, Node *new_node) {
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