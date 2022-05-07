/*
    Rafael Anderson Dalmolin
    Engenharia de Computação
    RA 1436287
    SISTEMAS OPERACIONAIS
*/
// Rodar primeiro o cozinheiro, depois o gaules.
// gcc consumidor_sharemem.c -o consumidor_sharemem -lrt -lpthread
#include <stdio.h> 
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>

#define NUM_GAULESES 6
#define QUANT_JAVALIS 14
#define mainSleepTime 10

typedef struct shmbuf{
	pthread_mutex_t mutex;
	sem_t full,empty;
	int counter;
} shmbuf_t;

shmbuf_t *ptr;
char nome[NUM_GAULESES] = "RAFAEL";
int gaules[NUM_GAULESES];


int random_number(){
	return ( (rand() % 5) );
}

void RetiraJavali(int* gaules){
	sleep(random_number());
	pthread_mutex_lock(&(ptr->mutex)); 
	
	if(ptr->counter == 0 ){			

	    printf("Gaules %c(%d): Acordou o cozinheiro\n",nome[*gaules],*gaules);
		printf("Gaules %c(%d): Avisou cozinheiro sobre mesa vazia\n",nome[*gaules],*gaules);
		for(int i=0; i<QUANT_JAVALIS; i++){
			sem_post(&(ptr->empty));     
		}
	}
	
	sem_wait(&(ptr->full)); 
	ptr->counter --;
	pthread_mutex_unlock(&(ptr->mutex));
	printf("Gaules %c(%d): Comendo javali[%d]\n",nome[*gaules],*gaules,((ptr->counter)+1));
}
void* Gaules(int* gaules){
	while(true){
		RetiraJavali(gaules);
	}
}

int main(void){
	sleep(2);
	int fd;
	
	fd = shm_open("sharedmen",O_RDWR|O_CREAT,S_IRUSR|S_IWUSR);
	ftruncate(fd,sizeof(shmbuf_t));
	ptr =mmap(NULL,sizeof(shmbuf_t),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	
	pthread_t gauleses[NUM_GAULESES];
	
	long status, i;
	for(i=0; i<NUM_GAULESES; i++){
		gaules[i]=i;
		printf("cria trhead [%ld]\n",i);
		status = pthread_create(&gauleses[i],NULL,(void *)Gaules,(int *)&gaules[i]);
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
