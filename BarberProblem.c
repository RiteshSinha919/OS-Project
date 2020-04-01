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

