#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<unistd.h>
#include<pthread.h>
#include<time.h>
#define max_client 20

void *client(void *n);
void *hair_stylist(void *);
void wait_time(int sec);

sem_t chair_for_client;
sem_t chair_for_hair_stylist;
sem_t chair_for_sleeping;
sem_t waiting_time_for_client;

int finished=0;
int main(int argc,char *argv[])
{
	pthread_t btid;
	pthread_t tid[max_client];
	int i,num_client,num_seat;
	int buff[max_client];
	printf("Enter the number of clients : \n");
	scanf("%d",&num_client);
	printf("Enter the number of seats : \n");
	scanf("%d",&num_seat);
	if(num_client > max_client)
	{
		printf("Maximum number of clients is %d \n",max_client);
		system("PAUSE");
		return 0;
	}
	for(i=0;i<max_client;i++)
	{
		buff[i]=i;
	}
	
	sem_init(&chair_for_client,0,num_seat);
	sem_init(&chair_for_hair_stylist,0,1);
	sem_init(&chair_for_sleeping,0,0);
	sem_init(&waiting_time_for_client,0,0);
	
	pthread_create(&btid,NULL,hair_stylist,NULL);
	for(i=0;i<num_client;i++)
	{
		pthread_create(&tid[i],NULL,client,(void *)&buff[i]);
	}
	for(i=0;i<num_client;i++)
	{
		pthread_join(tid[i],NULL);
	}
	finished=1;
	sem_post(&chair_for_sleeping);
	pthread_join(btid,NULL);
	system("PAUSE");
	return 0;
}


void wait_time(int sec)
{
	int size=1;
	sleep(size);
}

void *hair_stylist(void *style)
{
	while(!finished)
	{
		printf("The Hair Stylist is sleeping \n");
		sem_wait(&chair_for_sleeping);
		if(!finished)
		{
			printf("The hair stylist is cutting the hair \n");
			wait_time(4);
			printf("The hair stylist has finished cutting hair \n");
			sem_post(&waiting_time_for_client);
		}
		else
		{
			printf("Time to close the shop \n");
		}
	}
}

void *client(void *change)
{
	int n = *(int *)change;
	printf("Client %d is leaving for hair stylist's shop \n",n+1);
	wait_time(4);
	printf("Client %d arrived at hair stylist's shop \n",n+1);
	sem_wait(&chair_for_client);
	printf("Client %d entering waiting room \n",n+1);
	sem_wait(&chair_for_hair_stylist);
	sem_post(&chair_for_client);
	printf("Client %d is waking the hair stylist \n",n+1);
	sem_post(&chair_for_sleeping);
	sem_wait(&waiting_time_for_client);
	sem_post(&chair_for_hair_stylist);
	printf("Client %d is leaving the hair stylist's shop \n",n+1);
}
