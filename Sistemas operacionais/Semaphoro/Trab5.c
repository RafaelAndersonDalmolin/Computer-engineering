#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<pthread.h>
#include<semaphore.h>
sem_t A,B,C,D,E,G,H;
int x=0,y=0,z=0,h=0,j=0,u=0;
void ProcA(){
    printf("Iniciando processo 'A' \n"); 
	x=1;
	y=1;
	z=2;
	printf("x=1 y=1 z=2 \n");
    printf("Finalizando processo 'A' \n");
	sem_post(&A);
}
void ProcB(){
	sem_wait(&A);
    printf("Iniciando processo 'B' \n"); 
    x=x*2;
	printf("x=x*2 \n");
    printf("Finalizando processo 'B' \n");
    sem_post(&B);
	sem_post(&A);
}
void ProcC(){
	sem_wait(&B);
    printf("Iniciando processo 'C' \n"); 
    x=x+1;
	printf("x=x+1 \n");
    printf("Finalizando processo 'C' \n");
	sem_post(&B);
	sem_post(&C);
}
void ProcD(){
	sem_wait(&C);
	sem_wait(&E);
    printf("Iniciando processo 'D' \n"); 
    h=y+x;
	printf("h=y+x \n");
    printf("Finalizando processo 'D' \n");
    sem_post(&C);
    sem_post(&E);
    sem_post(&D);
}
void ProcE(){
	sem_wait(&A);
    printf("Iniciando processo 'E' \n"); 
    y=y+2;
	printf("y=y+2 \n");
    printf("Finalizando processo 'E' \n");
	sem_post(&A);
	sem_post(&E);
}
void ProcF(){
	sem_wait(&D);
	sem_wait(&H);
    printf("Iniciando processo 'F' \n"); 
    u=h+(j/3);
	printf("u=h+(j/3) \n");
    printf("Finalizando processo 'F' \n");
	sem_post(&D);
	sem_post(&H);
}
void ProcG(){
	sem_wait(&A);
    printf("Iniciando processo 'G' \n"); 
    z=z/2;
	printf("z=z/2 \n");
    printf("Finalizando processo 'G' \n");
	sem_post(&A);
	sem_post(&G);
}
void ProcH(){
	sem_wait(&E);
	sem_wait(&G);
    printf("Iniciando processo 'H' \n"); 
    j=z+y-4;
	printf("j=z+y-4 \n");
    printf("Finalizando processo 'H' \n");
	sem_post(&E);
	sem_post(&G);
	sem_post(&H);
}

void* Proc1(void*	 P){
	printf("P1: begin A; E; F;\n"); 
	ProcA();
	ProcE();
	ProcF();
	printf("P1: End\n"); 
}
void* Proc2(void* P){
	printf("P2: begin B; C; D;\n"); 
	ProcB();
	ProcC();
	ProcD();
	printf("P2: End\n"); 
}
void* Proc3(void* P){
	printf("P3: begin G; H;\n"); 
	ProcG();
	ProcH();
	printf("P3: End\n"); 
}
void main (void){  	
	pthread_t thread[3];
	sem_init(&A, 0, 0); 
    sem_init(&B, 0, 0);
    sem_init(&C, 0, 0);		
    sem_init(&D, 0, 0);	
    sem_init(&E, 0, 0);	
    sem_init(&G, 0, 0);	
    sem_init(&H, 0, 0);	
    
	pthread_create(&thread[0], NULL, &Proc1, NULL);
    pthread_create(&thread[1], NULL, &Proc2, NULL);
    pthread_create(&thread[2], NULL, &Proc3, NULL);
	
	for(int i=0; i<3; i++) {
        pthread_join (thread[i], NULL);
    }
	printf("Valores Finais das variaveis X=%d ,Y=%d ,Z=%d ,H=%d ,J=%d ,U=%d \n", x, y, z, h, j, u);
	exit(0);

}
