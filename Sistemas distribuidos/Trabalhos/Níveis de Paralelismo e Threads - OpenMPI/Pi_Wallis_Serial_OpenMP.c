// Approximation of the number pi through the Wallis's series
#include <stdio.h>
#include <omp.h>
#define BILHAO 1000000000

void main(void){
	double pi=1;
	double wall_timer = omp_get_wtime();
	for(double i = 1; i <= BILHAO; i++){
	    pi *=  ((((2*i)/((2*i)-1)) * ((2*i)/((2*i)+1))));
	}
	printf("Time on wall:\t%f\n",omp_get_wtime()-wall_timer);
	printf("\nAproximated value of PI = %1.80lf\n",pi*2);
}
