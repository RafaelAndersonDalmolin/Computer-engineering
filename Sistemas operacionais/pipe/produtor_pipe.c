/*
	Rafael Anderson Dalmolin	
    Engenharia de Computação
    RA 1436287
    SISTEMAS OPERACIONAIS
*/
// gcc produtor_pipe.c -o produtor_pipe -lrt -lpthread
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdbool.h>

#define NUM_COZINHEIROS 1
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

void initializeData(){
	pthread_mutex_init(&mutex,NULL);
	ptr->counter=0;
}

int random_number(){
	return ( (rand() % 100) );
}

void ColocaJavalis(int* cozin){

		pthread_mutex_lock(&mutex); 
		
        read(fdr, ptr, sizeof(pipebuf_t));
        while(ptr->counter < QUANT_JAVALIS){

			ptr->javali[ptr->counter] = random_number();
			printf("Cozinheiro [%d] fez o javali [%d] \n",*cozin,(int)ptr->javali[ptr->counter]);
			ptr->counter++;
		}
        write(fdw, ptr, sizeof(pipebuf_t));
        printf("Vou dormir, me acordem quando a mesa estiver vazia\n");
		pthread_mutex_unlock(&mutex);
		
}
void* Cozinheiro(int* cozin){
	while(true){
		ColocaJavalis(cozin);
	}
}


int main(void){
	
	mkfifo("Myfifo1", 0666);
    mkfifo("Myfifo2", 0666);

    fdw = open("Myfifo1", O_WRONLY);
    fdr = open("Myfifo2", O_RDONLY);

	initializeData();
	
	pthread_t cozinheiro[NUM_COZINHEIROS];
	int cozin[NUM_COZINHEIROS];
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
