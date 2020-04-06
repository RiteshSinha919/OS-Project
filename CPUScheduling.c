#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
void main()
{
    int burstt[20],process[20],waitingt[20],turnaroundt[20],i,j,n,total=0,pos,temp;
    float avg_waitingt,avg_turnaroundt;
    printf("Enter number of process:");
    scanf("%d",&n);
 
    printf("\nEnter Burst Time:\n");
    for(i=0;i<n;i++)
    {
        printf("p%d:",i+1);
        scanf("%d",&burstt[i]);
        process[i]=i+1;          
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
    }
 
    waitingt[0]=0;                    
 

    for(i=1;i<n;i++)
    {
        waitingt[i]=0;
        for(j=0;j<i;j++)
            waitingt[i]+=burstt[j];
 
        total+=waitingt[i];
    }
 
    avg_waitingt=(float)total/n;      
    total=0;
 
    printf("\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time");

    for(i=0;i<n;i++)
    {
        turnaroundt[i]=burstt[i]+waitingt[i];    
        total+=turnaroundt[i];
        printf("\np%d\t\t  %d\t\t    %d\t\t\t%d",process[i],burstt[i],waitingt[i],turnaroundt[i]);
    }
 
    avg_turnaroundt=(float)total/n; 
    printf("\n\nAverage Waiting Time=%f",avg_waitingt);
    printf("\nAverage Turnaround Time=%f\n",avg_turnaroundt);
}
