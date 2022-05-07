/*
    Rafael Anderson Dalmolin
    Engenharia de Computação
    RA 1436287
    SISTEMAS OPERACIONAIS
*/
// Rodar primeiro o cozinheiro, depois o gaules.
// gcc produtor_sharemem.c -o produtor_sharemem -lrt -lpthread

#include <stdio.h> 
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>

#define NUM_COZINHEIROS 1
#define QUANT_JAVALIS 14
#define mainSleepTime 15


typedef struct shmbuf{
	pthread_mutex_t mutex;
	sem_t full,empty;
	int counter;
} shmbuf_t;

int cozin[NUM_COZINHEIROS];
shmbuf_t *ptr;

void initializeData(){
	ptr->counter = 0;
	pthread_mutex_init(&(ptr->mutex),NULL);
	sem_init(&(ptr->full),1,0);
	sem_init(&(ptr->empty),1,QUANT_JAVALIS);
}
void ColocaJavalis(int* cozin){
		sem_wait(&(ptr->empty));     
		ptr->counter++;
		printf("Cozinheiro [%d] fez o javali [%d] \n",*cozin,ptr->counter);
		sem_post(&(ptr->full));
}
void* Cozinheiro(int* cozin){
	while(true){
		ColocaJavalis(cozin);
	}
}

int main(void){
	int fd;
	
	fd = shm_open("sharedmen",O_RDWR|O_CREAT,S_IRUSR|S_IWUSR);
	ftruncate(fd,sizeof(shmbuf_t));
	ptr =mmap(NULL,sizeof(shmbuf_t),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	
	initializeData();
	pthread_t cozinheiro[NUM_COZINHEIROS];
	long status, i;
	
	for(i=0; i<NUM_COZINHEIROS; i++){
		printf("cria trhead [%ld]\n",i);
		cozin[i]=i;
		status = pthread_create(&cozinheiro[i],NULL,(void *)Cozinheiro,(int *)&cozin[i]);
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
