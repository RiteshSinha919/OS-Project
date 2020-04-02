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
	printf("Enter te number of clients : \n");
	scanf("%d",&num_client);
	printf("Enter te number of seats : \n");
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
