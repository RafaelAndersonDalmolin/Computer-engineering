#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define NUM_COZINHEIROS 1
#define NUM_GAULESES 6
#define QUANT_JAVALIS 14

pthread_mutex_t mutex;
sem_t full,empty;
int counter;
char nome[NUM_GAULESES] = "RAFAEL";
int mainSleepTime = 10;
int gaules[NUM_GAULESES];

int random_number(){
	return ( (rand() % 5) );
}
void initializeData(){
	counter = 0;
	pthread_mutex_init(&mutex,NULL);
	sem_init(&full,0,0);
	sem_init(&empty,0,QUANT_JAVALIS);
}

void RetiraJavali(int* gaules){
	sleep(random_number());
	pthread_mutex_lock(&mutex); 
	if(counter == 0 ){
	    printf("Gaules %c(%d): Acordou o cozinheiro\n",nome[*gaules],*gaules);
		sem_post(&empty);
		for(int i=0; i<QUANT_JAVALIS-1; i++){
			sem_post(&empty);
		}
		sem_wait(&full); 
	}
	counter--;
	pthread_mutex_unlock(&mutex);
	printf("Gaules %c(%d): Comendo\n",nome[*gaules],*gaules);
}
void ColocaJavalis(){
		sem_wait(&empty);     
		counter++;
		printf("Cozinheiro fez um javali \n");
		sem_post(&full);
}
void* Gaules(void* gaules){
	while(true){
		RetiraJavali((int *)gaules);
	}
}
void* Cozinheiro(){
	while(true){
		ColocaJavalis();
	}
}
void main(void){
	initializeData();
	pthread_t cozinheiro[NUM_COZINHEIROS];
	pthread_t gauleses[NUM_GAULESES];

	
	for(int i=0; i<NUM_COZINHEIROS; i++){
		pthread_create(&cozinheiro[i],NULL,Cozinheiro,NULL);
	}
	
	for(int i=0; i<NUM_GAULESES; i++){
		gaules[i]=i;
		status = pthread_create(&gauleses[i],NULL,Gaules,&gaules[i]);
		if (status) // ocorreu um erro
		{
			perror ("pthread_create");
			exit (-1);
		}
	}

	sleep(mainSleepTime);
	printf("Exit the program\n");
	pthread_exit(NULL);
	exit(0);
}
