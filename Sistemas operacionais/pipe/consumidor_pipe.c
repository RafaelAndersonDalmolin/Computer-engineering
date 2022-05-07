/*
	Rafael Anderson Dalmolin	
    Engenharia de Computação
    RA 1436287
    SISTEMAS OPERACIONAIS
*/
// gcc consumidor_pipe.c -o consumidor_pipe -lrt -lpthread
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdbool.h>

#define NUM_GAULESES 6
#define QUANT_JAVALIS 14
#define mainSleepTime 15

typedef struct pipebuf{
	int javali[QUANT_JAVALIS];
	int counter;
} pipebuf_t;

pipebuf_t data;
pipebuf_t *ptr = &data;

pthread_mutex_t mutex;
int fdw,fdr;
char nome[NUM_GAULESES] = "RAFAEL";

void initializeData(){
	pthread_mutex_init(&mutex,NULL);
	ptr->counter=0;
}

int random_number(){
	return ( (rand() % 5) );
}

void RetiraJavali(int* gaules){

	pthread_mutex_lock(&mutex); 
	if(ptr->counter == 0 ){			

	    printf("Gaules %c(%d): Acordou o cozinheiro\n",nome[*gaules],*gaules);
		printf("Gaules %c(%d): Avisou cozinheiro sobre mesa vazia\n",nome[*gaules],*gaules);
        write(fdw, ptr, sizeof(pipebuf_t));
        read(fdr, ptr, sizeof(pipebuf_t));
	}
	ptr->counter --;
	printf("Gaules %c(%d): Comendo javali[%d]\n",nome[*gaules],*gaules,(int)ptr->javali[ptr->counter]);
	pthread_mutex_unlock(&mutex);
	sleep(random_number());
}

void* Gaules(int* gaules){
	while(true){
		RetiraJavali(gaules);
	}
}

int main(void){
	
	mkfifo("Myfifo1", 0666);
    mkfifo("Myfifo2", 0666);

    fdr = open("Myfifo1", O_RDONLY);
    fdw = open("Myfifo2", O_WRONLY);


	initializeData();
	
	pthread_t gauleses[NUM_GAULESES];
	int gaules[NUM_GAULESES];
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
