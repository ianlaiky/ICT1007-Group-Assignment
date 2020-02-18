// Round Robin Algorithm
// To implement SJF into Round Robin Algorithm
#include<stdio.h> 

main() {
	/* 
	Declare int variable for usage
	i, n & j = counter
	bu = burst time array
	wa = waiting time array
	tat = turnaround time array
	t = time slice
	ct = another burst time array (burst time according to code)
	max = literally max
	*/
	int i, j, n, bu[20], wa[20], tat[20], t, ct[20], max;

	/* 
	Declare float variable for usage
	awt = average waiting time
	att = average turnaround time
	temp = temporary
	*/
	float awt=0, att=0, temp=0;

	/* text to be written to stdout */ 
	printf("Enter the no of processes: ");

	/* read user data from stdin, # of process */
	scanf("%d",&n); 

	/* let user input their burst time according to their number of processes 
	   eg processes #1 -> 3 unit burst time	
	*/
	for(i=0; i<n; i++)   {
		/* i increment by 1 so stdout to user that it is inputing process 1 */
		printf("\nEnter Burst Time for process %d: ", i+1);
		/* read user data from stdin, burst time and put into array*/
		scanf("%d", &bu[i]);
		/* copy value into cpu time array*/
		ct[i]=bu[i];  
	}  
	
	/* text to be written to stdout */
	printf("\nEnter the size of time slice: ");  

	/* read user data from stdin, time slice (how long can a process use (unit)) */
	scanf("%d",&t);  

	/* max = bu[0] value*/
	max=bu[0];  
	/* get the largest burst time */
	for(i=1; i<n; i++)
		if(max<bu[i])
			max=bu[i];  
	
	/* it will guarantee a completed run of the smaller quantums */
	for(j=0; j<(max/t)+1; j++)  
	{   
		/* for each process */
		for(i=0; i<n; i++)   { 
			/* if bursttime of the process is not 0 */   
			if(bu[i]!=0)
				/* If the burst time is less than the time slice then
				   
				   set tat = temp + the current burst time
				   set temp =  last temp plus current burst time.
				   set current burst time to 0
				*/
				if(bu[i]<=t){
					tat[i]=temp+bu[i];
					temp=temp+bu[i];
					bu[i]=0;
					}
				/* else if burst time is bigger than time slice then
				   
				   set current burst = current burst - time slice
				   process has yet to finish it's job
				   set temp = temp + time slice
				 */
				else{
					bu[i]=bu[i]-t;
					temp=temp+t;
				}  
		}

	} 
	/* for each process */
	for(i=0;i<n;i++)
	{
		/*current process waiting time = current turnaround - current burst time*/ 
		wa[i]=tat[i]-ct[i];
		/* get total turnaround time */
		att+=tat[i];
		/* get total waiting time */
		awt+=wa[i];
	}

	printf("\n\nUsing Round Robin Scheduling\n");

	/* print out process # burst time, waiting time, turnaround time */
	printf("\n\tPROCESS\t BURST TIME \t WAITING TIME \t TURNAROUND TIME\n");
	for(i=0;i<n;i++){
		printf("\t%d \t %d \t\t %d \t\t %d \n",i+1,ct[i],wa[i],tat[i]);
	}

	/* Average Waiting time = Total waiting time / no of process
	   Average Turnaround time = Total turnaround time / no of process
	*/
	printf("\n\nAverage Waiting Time= %f",awt/n); 
  	printf("\nAverage Turnaround Time = %f\n",att/n); 
	
	return 0;
} 
