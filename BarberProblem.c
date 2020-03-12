#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
int main()
{
pid_t p;
int m,seats,count=0;
printf("Enter the number of seats in waiting room of barbershop : \n");
scanf("%d \n",&maxSeat);
int arr[maxSeat];
printf("Enter the initial number of customers waiting in the waiting room : \n");
scanf("%d \n",&initial);
p=fork();
	if(p<0)
	{

	}
	else if(p==0)
	{
		if(count==maxSeat)
		{
			printf("Seats are full \n");
			sleep(2);
		}
		else if(count<maxSeat)
		{
			printf("You can wait in the waiting room until your turn comes");
		}
	}
}