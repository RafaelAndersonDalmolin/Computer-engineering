#include <stdio.h>
#include <mpi.h>
#include <math.h>
#include <stdbool.h>

int isprime(long long int num,long start, long end){
 	 if (num > 1){
   	 for (int i = start; i < end; i++){
    	 if (num % i == 0){
   	     	return 0;
		 }
   	 }
   	 return 1;
  	}

  	else{
	    return 0;
	}
}

int main(int argc, char **argv){
  int result=0;	
  int primo;
  int primo_parc;
  long long int num = 982451653;
  double begin = MPI_Wtime();
  int size, rank;
  long start, end;

  MPI_Status status;
  MPI_Init(&argc, &argv); // daqui pra baixo, ocorre o paralelismo e acaba no MPI_Finalize
  MPI_Comm_size(MPI_COMM_WORLD, &size);// size é o numero de threads q vc passou como argumento
  MPI_Comm_rank(MPI_COMM_WORLD, &rank); // rank é o numero da thread q vc está

  start = ((num * rank) / size) + 2; 
  end = ((num * (rank + 1)) / size);

  primo= isprime(num,start,end);

  printf("Process %d: start = %10ld, end = %ld | primo = %d\n", rank, start, end, primo);

  if(rank != 0){
    	MPI_Send(&primo, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
  }
  else{
	//printf("Entrou calcular o result %d\n", result);
    for (long j = 1; j < size; j++){
      MPI_Recv(&primo_parc, 1, MPI_INT, j, 1, MPI_COMM_WORLD, &status);
      result += primo_parc;
    }
	result += primo;
	//printf("terminou calcular o result %d\n", result);
  }

  if(rank == 0){
	//printf("Entrou %d\n", result);
    double end = MPI_Wtime();
    double time_spent = (double)(end - begin);
	if(result==size){
		printf("O numero %Ld é primo\n",num);
	}
	else{
		printf("O numero %Ld não é primo\n",num);
	}
    printf("Tempo: %.10lf\n",time_spent);
  }

  MPI_Finalize();
  return 0;
}
