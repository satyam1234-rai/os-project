#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <string.h>
#include<fcntl.h>
#include<pthread.h>
pthread_mutex_t plock;
int main()
{
pthread_mutex_init(&plock, NULL);
int no_of_process,p[10]={1,2,3,4,5,6,7,8,9,10},min,k=1,btime=0;
int bt[10],temp,at[10],wt[10],tt[10],ta=0,sum=0;
float avg_waiting_time=0,avg_turn_arr_time=0,tat_sum=0,waiting_sum=0;
printf(" -------SJF Scheduling ( Non-Preemtitive )-------\n");
printf("\nEnter the number of processes :");
scanf("%d",&no_of_process);

for(int i=0;i<no_of_process;i++)
{
        
        printf("\nEnter Details For P%d\n",i+1);
	pthread_mutex_lock(&plock);
	label:
        printf("Arrival time:");
        scanf("%d",&at[i]);
	if (at[i]==0)
	{
		printf("\n Arrival time should not be zero!!!! Re-enter the correct arrival time \n");
		goto label;
	}	
        bt[i]=at[i]*2;
        printf("Burst Time:%d\n",bt[i]);
        printf("----------------------------------------");
	pthread_mutex_unlock(&plock);
}
for(int i=0;i<no_of_process;i++)
{
	for(int j=0;j<no_of_process;j++)
	{
		if(at[i]<at[j])
		{
			temp=p[j];
			p[j]=p[i];
			p[i]=temp;
			temp=at[j];
			at[j]=at[i];
			at[i]=temp;
			temp=bt[j];
			bt[j]=bt[i];
			bt[i]=temp;
		}
	}
}



for(int j=0;j<no_of_process;j++)
{
	btime=btime+bt[j];
	min=bt[k];
		for(int i=k;i<no_of_process;i++)
			{
			if (btime>=at[i] && bt[i]>min)
				{
					temp=p[k];
					p[k]=p[i];
					p[i]=temp;
					temp=at[k];
					at[k]=at[i];
					at[i]=temp;
					temp=bt[k];
					bt[k]=bt[i];
					bt[i]=temp;
				}
			}
	k++;
}

wt[0]=0;
for(int i=1;i<no_of_process;i++)
{
		wt[i]=0;
		for(int j=0;j<i;j++)
			wt[i]+=bt[j];
		waiting_sum += wt[i];
}

avg_waiting_time=(waiting_sum/no_of_process);
	for(int i=0;i<no_of_process;i++)
	{
	ta=ta+bt[i];
	tt[i]=ta-at[i];
	tat_sum +=tt[i];
	}

avg_turn_arr_time=(tat_sum/no_of_process);

printf("\n Results:-");
printf("\nProcess ID\t Burst Time\t Arrival Time\t Waiting Time\t Turn around Time" );
for(int i=0;i<no_of_process;i++)
{
	printf("\n p%d\t %d\t %d\t\t %d\t\t\t%d",p[i],bt[i],at[i],wt[i],tt[i]);
}

printf("\n\nAVERAGE WAITING TIME : %f",avg_waiting_time);
printf("\nAVERAGE TURN AROUND TIME : %f\n",avg_turn_arr_time);
return 0;
}
