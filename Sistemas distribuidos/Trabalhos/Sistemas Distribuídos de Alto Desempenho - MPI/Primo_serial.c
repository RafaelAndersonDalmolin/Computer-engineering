#include <stdio.h>
#include <mpi.h>
#include <math.h>
#include <stdbool.h>

int isprime(long long int num){
 	 if (num > 1){
   	 for (int i = 2; i < num; i++){
    	 if (num % i == 0){
   	     	return false;
		 }
   	 }
   	 return true;
  	}

  	else{
	    return false;
	}

}

int main(int argc, char *argv[]){
	int primo;
	long long int num = 982451653;

	double begin = MPI_Wtime(); 
	
	//chama funçao verifica primo
	primo= isprime(num);

	// calcula o tempo
	double end = MPI_Wtime();
    double time_spent = (double)(end - begin);
	if(primo){
		printf("O numero %Ld é primo\n",num);
	}
	else{
		printf("O numero %Ld não é primo\n",num);
	}
    printf("Tempo: %.10lf\n",time_spent);

    return 0;
}
