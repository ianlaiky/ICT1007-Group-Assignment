#include<stdio.h> 

int main() {
	/* 
	Declare int variable for usage
	i, n, j and o = counter
	bu = burst time array
	wa = waiting time array
	tat = turnaround time array
	at = average time slice
	ct = another burst time array (burst time according to code)
	max = literally max
	*/
	int i, j, o, k, m, wa[20], tat[20], at, ct[20], max, process[20], sum;
	int bu[20]={23, 19, 10, 11, 5}; // dynamic burst time for each process
	int n = 6; // dynamic number of processes
	/* 
	Declare float variable for usage
	awt = average waiting time
	att = average turnaround time
	temp = temporary
	*/
	float awt=0, att=0, temp=0;
	/* let user input their burst time according to their number of processes 
	   eg processes #1 -> 3 unit burst time	
	*/
	for(i=0; i<n; i++)   {
		process[i]=i;
		ct[i]=bu[i];  
	}  
	
	for(o=0;o<n;o++)
	{
		for(k=o+1;k<n;k++)
		{
			if(bu[o]>bu[k])
				{
					temp=bu[o];
					ct[o] = bu[o]=bu[k];
					ct[k] = bu[k]=temp;

					temp=process[o];
					process[o]=process[k];
					process[k]=temp;
				}
		}	
	}
	temp  = 0;
	for (m=0; m<n; m++) 
	{
		sum += bu[m];
	}
	at = sum/n; 

	/* max = bu[0] value*/
	max=bu[0];  
	/* get the largest burst time */
	for(i=1; i<n; i++)
		if(max<bu[i])
			max=bu[i];  
	
	/* it will guarantee a completed run of the smaller quantums */
	for(j=0; j<(max/at)+1; j++)  
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
				if(bu[i]<=at){
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
					bu[i]=bu[i]-at;
					temp=temp+at;
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

	printf("\n\nUsing Sorted Round Robin Scheduling\n");

	/* print out process # burst time, waiting time, turnaround time */
	printf("\n\tPROCESS\t BURST TIME \t WAITING TIME \t TURNAROUND TIME\n");
	for(i=0;i<n;i++){
		printf("\t%d \t %d \t\t %d \t\t %d \n",process[i]+1,ct[i],wa[i],tat[i]);
	}

	/* Average Waiting time = Total waiting time / no of process
	   Average Turnaround time = Total turnaround time / no of process
	*/
	printf("\n\nAverage Waiting Time= %f",awt/n); 
  	printf("\nAverage Turnaround Time = %f\n",att/n); 
	printf("\nAverage Time Slice %d", at);
	
	return 0;
} 
