// Approximation of the number pi through the Leibniz-gregory-madhava series
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>


#define NUM_THREAD 16
#define BILHAO 1000000000
double result = 0;
double parc[8*NUM_THREAD];

void* calc_pi(void* tid){
	//printf("Calculating thread %ld\n",(long)tid);
	long Tid = (long)tid;
	
	unsigned long int termos = BILHAO / NUM_THREAD;
	unsigned long int inicio = Tid * termos;
	unsigned long int fim = Tid * termos + termos;
	double s = 1;
	
	//printf("valores inicio %ld\n",inicio);		printf("valores fim %ld\n",fim);
       
	for(double i= (inicio +1); i <= ((fim*2)+1); i+=2){  
		parc[8*Tid] += ( s * (4 / i) );
		s = -s;
		/*if(Tid ==1){
			printf("for thread %ld\n",Tid);
			printf("valores inicio %.80lf\n",parc[8*Tid] );
		}*/
	}
    //pthread_exit(0);
}

void main(void) {

	pthread_t thread[NUM_THREAD];
	long status,i;

	for(i=0; i<NUM_THREAD; i++){
		parc[8*i]=0;
		//printf("valores parciais %lf\n",parc[8*i]);
	}
	
	for(i=0; i<NUM_THREAD; i++){
		//printf("Creating thread %ld\n",i);
		status = pthread_create(&thread[i],NULL,calc_pi,(void *)(intptr_t)i);
	}
	

	if(status){ // Verifica se ocorreu um erro na criacao de thread
		perror("pthread_create");
		exit(-1);	
	}
	
	for(i=0; i<NUM_THREAD; i++){
        pthread_join(thread[i], NULL);
        //printf("valores parciais %1.80lf\n",parc[8*i]);
        result +=parc[8*i];
	}
	printf("\nAproximated value of PI = %1.80lf\n",result); 
    pthread_exit(0);
}
