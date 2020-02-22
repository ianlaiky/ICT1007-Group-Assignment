#include <stdio.h>

#define iBurstTime {23, 19, 10, 11, 5}
#define PRIORITY {4, 2, 1, 3, 5}
#define TIMESLICE 5

main()
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
	int i, j, n, bu[20], wa[20], tat[20], t, ct[20], max, pl[20], a, pn[20], index[20];
	float awt=0, att=0, temp=0;
	bool empty=0
	
	for(i=0; i<20; i++)
	{
		if(iBurstTime[i])
		{
			bu[i]=iBurstTime[i];
			ct[i]=bu[i];
			pl[i]=PRIORITY[i];
			pn[i]=i+1;
		}
	}
	
	n=sizeof(bu)/sizeof(int);
	printf("Number of Processes = %d", n);
	
	t=TIMESLICE;
	printf("Time Slice = %d", t);
	
	//Indexing algo
	for (i = 0; i < n; i++) 
	{
		index[pl[i]] =  bu[i];
	}
	
	for (i = 0; i < n; i++)
	{
		bu[i] = index[i];
		pl[i] = i;
	}
	
	for(i=0; i<n; i++)
	{
		if(bu[i]!=0)
		{
			empty=0;
			break;
		}
		empty=1;
	}
	
	while(!empty)
	{
		// Loop each process
		for(i=0; i<n; i++)
		{
			// If bu[i] = 0, means the process has already been completed, move on to next process.
			if(bu[i]!=0)
				// If bu[i] time lesser than or equal to time slice/quantum,
				if(bu[i]<=t)
				{
					// Add to temp & turn around time array.
					tat[i]=temp+bu[i];
					temp=temp+bu[i];
					// Set time left to complete process to 0.
					bu[i]=0;
					n-=1;
				}
				else
				{
					// Deduct time slice/quantum from remaining burst time for current process.
					bu[i]=bu[i]-t;
					// Increment temp by t
					temp=temp+t;
				}
		}
		
		//Calculate new priority queue
		for(i=0; i<n; i++)
		{
			
		
		//Calculate new dynamic time quantum
		if(n%2==0)
		{
			
		}
		else
		{
			
		}
	}
	
	// ** Calculate and print the 'waiting time' and 'turn-around-time' for each process. **
	printf("\nProcess ID\tBurst Time\tTurnaround Time\t\tWaiting Time\n");
	for(i=0; i<n; i++)
	{
		// Turn Around Time - burst Time  = Waiting Time
		wa[i] = tat[i] - ct[i];
		printf("Process[%d]\t%d\t\t%d\t\t\t%d\n", i + 1, ct[i], tat[i], wa[i]);
		
		// Getting Total Waiting & Turn Around Time
		awt += wa[i];
		att += tat[i];
	}
	
	// Calculate Average Waiting & Turn Around Time
	printf("\nAverage Waiting Time:\t\t%.3f\n", awt/n);
	printf("Average Turn Around Time:\t%.3f\n", att/n);
}
