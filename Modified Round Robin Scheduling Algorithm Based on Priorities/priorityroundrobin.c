#include <stdio.h>

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
	int i, j, n, bu[20], wa[20], tat[20], t, ct[20], max, pl[20], a, pn[20], b;
	float awt=0, att=0, temp=0;
	
    int iBurstTime[] = {23, 19, 10, 11, 5};
    int priority_array[] = {4, 2, 1, 3, 5};
    t = 3;
	
	n=sizeof(iBurstTime)/sizeof(iBurstTime[0]);
	printf("Number of Processes = %d\n", n);
	printf("Time Slice = %d\n", t);
	
	//Indexing algo
    int temp_array[n];
	for (i = 0; i < n; i++) 
	{
		temp_array[priority_array[i]] =  iBurstTime[i];
	}
	
	for (i = 0; i < n; i++)
	{
		iBurstTime[i] = temp_array[i];
		priority_array[i] = i+1;
	}
    
	while(1)
	{
        int counter = 0;
        for(i=0;i<n;i++)
        {
            if(iBurstTime[i]==0)
            {
                counter++;
            }
        }
        
        if(counter==n)
        {
            break;
        }
        
		// Loop each process
		for(i=0; i<n; i++)
		{
			// If bu[i] = 0, means the process has already been completed, move on to next process.
			if(iBurstTime[i]!=0)
            {
                // If bu[i] time lesser than or equal to time slice/quantum,
				if(iBurstTime[i]<=t)
				{
					// Add to temp & turn around time array.
					tat[i]=temp+iBurstTime[i];
					temp=temp+iBurstTime[i];
					// Set time left to complete process to 0.
					iBurstTime[i]=0;
				}
				else
				{
					// Deduct time slice/quantum from remaining burst time for current process.
					iBurstTime[i]=iBurstTime[i]-t;
					// Increment temp by t
					temp=temp+t;
				}
            }
		}
		
        for(i=0;i<n;i++)
        {
            for(j=i+1;j<n;j++)
            {
                if(iBurstTime[j]==0)
                {
                    a = iBurstTime[i];
                    iBurstTime[i] = iBurstTime[j];
                    iBurstTime[j] = a;
                }
            }
        }
        
        
        //Calculate new burst time queue
        for(i=0;i<n;i++)
        {
            if(iBurstTime[i]==0)
            {
                b+=1;
            }
        }
        n = n-b;
        
        //Calculate new dynamic time quantum
        if(n%2==0)
        {
            t = (iBurstTime[priority_array[n/2]] + iBurstTime[1 + priority_array[n/2]])/2;
        }
        else
        {
             t = iBurstTime[priority_array[(n+1)/2]];
        }
    }
	
	// ** Calculate and print the 'waiting time' and 'turn-around-time' for each process. **
	printf("\nPROCESS\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n");
	for(i=0; i<n; i++)
	{
		// Turn Around Time - burst Time  = Waiting Time
		wa[i] = tat[i] - iBurstTime[i];
		printf("%d\t%d\t\t%d\t\t\t%d\n", i + 1, iBurstTime[i], wa[i], tat[i]);
		
		// Getting Total Waiting & Turn Around Time
		awt += wa[i];
		att += tat[i];
	}
	
	// Calculate Average Waiting & Turn Around Time
	printf("\nAverage Waiting Time:\t\t%.3f\n", awt/n);
	printf("Average Turn Around Time:\t%.3f\n", att/n);
}
