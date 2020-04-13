#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
void main()
{
    int burstt[20],process[20],waitingt[20],turnaroundt[20],queue[20],i,j,n,total=0,pos,temp,flag[20],div,div2;
    float avg_waitingt,avg_turnaroundt;
    printf("Enter number of process:");
    scanf("%d",&n);
 
    printf("\nEnter Burst Time:\n");
    for(i=0;i<n;i++)
    {
        printf("process%d:",i+1);
        scanf("%d",&burstt[i]);
        process[i]=i+1;          
    }
 	for(i=0;i<n;i++)
 	{
 		flag[i]=1;
	}


    for(i=0;i<n;i++)
    {
        pos=i;
        for(j=i+1;j<n;j++)
        {
            if(burstt[j]<burstt[pos])
                pos=j;
        }

        temp=burstt[i];
        burstt[i]=burstt[pos];
        burstt[pos]=temp;
 
        temp=process[i];
        process[i]=process[pos];
        process[pos]=temp;
    	if(burstt[i]>10)
    	{
    		div=burstt[i]/10;
    		flag[i]=div;
		}
    	printf("%d \n",flag[i]);
    }
 
    waitingt[0]=3;                    
 

    for(i=1;i<n;i++)
    {
        waitingt[i]=3;
        for(j=0;j<i;j++)
            waitingt[i]+=burstt[j] +3;
            
    }


    printf("\nProcess\t\t    Burst Time    \tWaiting Time\tTurnaround Time \n");
 
 	turnaroundt[0]=burstt[0]+waitingt[0];
    for(i=1;i<n;i++)
    {
        turnaroundt[i]=burstt[i]+waitingt[i]; 
    }
    for(i=0;i<n;i++)
    {
    	if(burstt[i]>10)
    	{
			turnaroundt[i]=(burstt[i]+waitingt[i])+(flag[i]*3);
			waitingt[i]=turnaroundt[i-1]+3;
		}
    	total+=turnaroundt[i];
    }
    avg_turnaroundt=(float)total/n; 
    total=0;
    for(i=0;i<n;i++)
    {
    	total+=waitingt[i];
    	printf("\nprocess %d\t\t  %d\t\t    %d\t\t\t%d",process[i],burstt[i],waitingt[i],turnaroundt[i]);
	}
 	avg_waitingt=(float)total/n;      
    printf("\n\nAverage Waiting Time=%f",avg_waitingt);
    printf("\nAverage Turnaround Time=%f\n",avg_turnaroundt);
}
