#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdint.h>
#include<pthread.h>
#include<semaphore.h>
sem_t A,B,D,E;

int random_number(){
	return ( (rand() % 6) );
}
void* ProcA (void* P){

    printf("Iniciando processo 'A' \n"); 
    sleep(random_number());
    printf("Finalizando processo 'A' \n");
	sem_post(&A);
}
void* ProcB (void* P){

    printf("Iniciando processo 'B' \n"); 
    sleep(random_number());
    printf("Finalizando processo 'B' \n");
	sem_post(&B);
}
void* ProcC (void* P){
	
	sem_wait(&A);
	sem_wait(&B);
    printf("Iniciando processo 'C' \n"); 
    sleep(random_number());
    printf("Finalizando processo 'C' \n");
	sem_post(&D);
	sem_post(&E);

}
void* ProcD (void* P){
	sem_wait(&D);
    printf("Iniciando processo 'D' \n"); 
    sleep(random_number());
    printf("Finalizando processo 'D' \n");

}
void* ProcE (void* P){
	sem_wait(&E);
    printf("Iniciando processo 'E' \n"); 
    sleep(random_number());
    printf("Finalizando processo 'E' \n");

}

void main (void){
  	srand(time(NULL));
  	
	pthread_t thread[5];
	sem_init(&A, 0, 0); 
    sem_init(&B, 0, 0);	
    sem_init(&D, 0, 0);	
    sem_init(&E, 0, 0);	
    
	pthread_create(&thread[0], NULL, &ProcA, NULL);
    pthread_create(&thread[1], NULL, &ProcB, NULL);
    pthread_create(&thread[2], NULL, &ProcC, NULL);
    pthread_create(&thread[3], NULL, &ProcD, NULL);
    pthread_create(&thread[4], NULL, &ProcE, NULL);
	
	for(int i=0; i<5; i++) {
        pthread_join (thread[i], NULL);
    }

	exit(0);

}
