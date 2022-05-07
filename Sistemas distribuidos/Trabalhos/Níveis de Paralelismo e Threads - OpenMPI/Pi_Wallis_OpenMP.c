// Approximation of the number pi through the Wallis's series
#include <stdio.h>
#include <omp.h>
#define BILHAO 1000000000
#define NUM_THREADS 16

int main(void){
	double pi=1;
	double parc[NUM_THREADS];
	int tid;		
	unsigned long int termos;
	unsigned long int inicio;
	unsigned long int fim;
	double wall_timer;
	printf("Number of threads:\t%d\n",NUM_THREADS);
	#pragma omp parallel num_threads(NUM_THREADS)
	{	
		for(int i= 0; i< NUM_THREADS; i++){
			parc[i]=1;
		}
	}
	wall_timer = omp_get_wtime();
	#pragma omp parallel if(NUM_THREADS >= 1) num_threads(NUM_THREADS) shared(parc) private(termos,inicio,fim,tid)
	{
		tid = omp_get_thread_num();		
		termos = BILHAO / NUM_THREADS;
		inicio = tid * termos;
		fim = tid * termos + termos;
		//printf("tid = %d\t termos = %li\t inicio = %li\t fim = %li\n",tid,termos,inicio,fim);
 
		for(double i = (inicio + 1); i <= fim; i++){
		    parc[tid] *=  ((((2*i)/((2*i)-1)) * ((2*i)/((2*i)+1))));
			//printf("\nAproximated value of PI = %1.80lf\n",pi); 
		}
	}
	printf("Time on wall:\t%f\n",omp_get_wtime()-wall_timer);
	for(int i= 0; i< NUM_THREADS; i++){
		pi = pi * parc[i];
	}
	printf("\nAproximated value of PI = %1.80lf\n",pi*2);
}
