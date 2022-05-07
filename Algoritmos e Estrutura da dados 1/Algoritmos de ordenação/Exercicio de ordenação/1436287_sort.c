#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include <time.h>
#include<stdlib.h>
#include<math.h>
#define MAX_VALUE 50000
double troca=0;
double comp =0;
double mediatemp=0;
double mediacomp=0;
double mediatroca=0;
clock_t t0;    // criamos uma variavel para marcar o tempo!
double tsecs; // criamos uma variavel para receber o tempo em segundos!
void exchange(){
	troca++;
}
void compare(){
	comp++;
}
bool maior(int a,int b){
	return a>b;
}
bool menorigual(int a, int b){
	return a<=b;
}
void swap(int* vetor, int a, int b){
    int aux = vetor[a];
    vetor[a] =vetor[b];
    vetor[b] = aux;
}
void fill_random(int* v, int size)  // gerar vetor aleatorio
{
	for(int i = 0; i < size; i++)
	{
		v[i] =rand()%MAX_VALUE;
	}
}
void cres_random(int* v, int size)  // gerar vetor aleatorio crescente
{
	v[0]=rand()%MAX_VALUE;
	for(int i = 1; i < size; i++)
	{
		v[i]=((v[i-1])+(rand()%MAX_VALUE));
	}
}
void decr_random(int* v, int size)  // gerar vetor aleatorio decrescente
{
	v[size-1]=rand()%100;
	for(int i = size-2; i >= 0; i--)
	{
		v[i]=(v[i+1])+(rand()%MAX_VALUE);
	}
}
void semi_random(int* v, int size)  // gerar vetor aleatorio crescente
{
	v[0]=rand()%100;
	for(int i = 1; i < size; i++){
		v[i]=(v[i-1])+(rand()%MAX_VALUE);
	}
	int x=(size*0.15);
	for(int i=0; i<x; i++){
		swap(v,(rand()%size),(rand()%size));
	}
}
void ordenado(int*v ,int size){   // verificar se o vetor esta ordenado
	for(int i = 0; i < size-1; i++)
	{
		if(v[i]>v[i+1]){
			printf("O VETOR ESTA DESORDENADO!\n");
			return;
		}
	}
	printf("O VETOR ESTA ORDENADO!\n");
}
void insertionsort(int* v, int size) {
	int atual,j;

	for (int i = 1; i < size; i++) {
		atual = v[i];
		exchange();
		for (j = i - 1; (j >= 0) && (atual < v[j]); j--) {
			v[j + 1] = v[j];
			exchange();
        }
		compare();
		exchange();
		v[j+1] = atual;
	}
}
void bubblesort(int* v, int size){

	for(int i=size-1; i>0; i--){
		for(int i=0; i<size-1; i++){
			compare();
			if(v[i]>v[i+1]){
				swap(v,i,i+1);
				exchange();
			}
		}
	}
}
void selectionsort(int* v, int size) {
	int min;
	for (int i = 0; i < (size-1); i++){
		min = i;
		for (int j = (i+1); j < size; j++) {
			if(v[j] < v[min]){
	     		min = j;
			}
			compare();
		}
	if (v[i] != v[min]){
		swap(v,i,min);
	 	exchange();
	}
  }
}
void merge(int* v, int* aux, int inicio, int meio, int fim){
	int i = inicio;
	int j = meio+1;
	int k = inicio;
	int t = inicio;

	for(k = inicio; k <= fim; k++)
	{
		if(i > meio)
		{
			aux[k] = v[j++];
		}
		else if(j > fim)
		{
			aux[k] = v[i++];
		}
		else if(menorigual(v[i], v[j]))
		{
			compare();
			aux[k] = v[i++];
		}
		else
		{
			aux[k] = v[j++];
			compare();

		}
		exchange();

	}
	for(t = inicio; t <= fim; t++)
	{
		v[t] = aux[t];
	}

}
void mergesort(int* v, int* aux, int inicio, int fim)
{
	if(inicio < fim)
	{
		int p = (fim+inicio)/2;
		mergesort(v, aux, inicio, p);
		mergesort(v,aux, p+1, fim);

		merge(v, aux,inicio, p, fim);
	}
}
int partition(int* A, int p, int r){
    int x = A[r];
    int i = p;
    int j = r;
    while (i < j) {
        while (A[i] <= x && i < r)
            i++;
        while (A[j] > x)
            j--;

        if (i < j){
            swap(A, i, j);
			exchange();
			compare();
		}
    }
	exchange();
    A[p] = A[j];
    A[r] = x;
    return r;
}
void quicksort(int* v, int inicio, int fim)
{
	if(inicio < fim)
	{
		int p = partition(v, inicio, fim);
		quicksort(v, inicio, p-1);
		quicksort(v, p+1, fim);
	}
}
int main(int argc, char** argv){
	int size = atoi(argv[1]);   // usa atoi para transformar a string em numero, que sera o size.
	int* v = malloc(sizeof(int)*size);	// aloca memoria para o vetor de tamanho size.
	int* aux=malloc(sizeof(int)*size);
	srand(time(NULL)); // dar uma semente para gerar aleatorio!


	for(int i=0; i<65; i++){

		troca=0;
		comp =0;
		t0 =0;
		tsecs=0;

		if(0==(strcmp(argv[2],"rand"))){
			fill_random(v,size);
		}
		if(0==(strcmp(argv[2],"cres"))){
			cres_random(v,size);
		}
		if(0==(strcmp(argv[2],"decr"))){
			decr_random(v,size);
		}
		if(0==(strcmp(argv[2],"semi"))){
			semi_random(v,size);
		}


		if(0==(strcmp(argv[3],"insertion"))){
			t0 =clock();
			insertionsort(v,size);
			t0 = clock() - t0;
			tsecs = (double) t0/CLOCKS_PER_SEC;
			printf("%.0lf\t%.0lf\t%.4lf\n",comp,troca,tsecs);
			mediatemp=mediatemp+tsecs;
			mediacomp=mediacomp+comp;
			mediatroca=mediatroca+troca;
		}
		if(0==(strcmp(argv[3],"bubble"))){
			t0 =clock();
			bubblesort(v,size);
			t0 = clock() - t0;
			tsecs = (double) t0/CLOCKS_PER_SEC;
			printf("%.0lf\t%.0lf\t%.4lf\n",comp,troca,tsecs);
			mediatemp=mediatemp+tsecs;
			mediacomp=mediacomp+comp;
			mediatroca=mediatroca+troca;

		}
		if(0==(strcmp(argv[3],"selection"))){
			t0 =clock();
			selectionsort(v,size);
			t0 = clock() - t0;
			tsecs = (double) t0/CLOCKS_PER_SEC;
			printf("%.0lf\t%.0lf\t%.4lf\n",comp,troca,tsecs);
			mediatemp=mediatemp+tsecs;
			mediacomp=mediacomp+comp;
			mediatroca=mediatroca+troca;
		}
		if(0==(strcmp(argv[3],"merge"))){
			t0 =clock();
			mergesort(v,aux,0,size-1);
			t0 = clock() - t0;
			tsecs = (double) t0/CLOCKS_PER_SEC;
			printf("%.0lf\t%.0lf\t%.4lf\n",comp,troca,tsecs);
			mediatemp=mediatemp+tsecs;
			mediacomp=mediacomp+comp;
			mediatroca=mediatroca+troca;
		}
	if(0==(strcmp(argv[3],"quick"))){
			t0 =clock();
			quicksort(v,0,size-1);
			t0 = clock() - t0;
			tsecs = (double) t0/CLOCKS_PER_SEC;
			printf("%.0lf\t%.0lf\t%.4lf\n",comp,troca,tsecs);
			mediatemp=mediatemp+tsecs;
			mediacomp=mediacomp+comp;
			mediatroca=mediatroca+troca;
		}
	}
	free(v);
	free(aux);
	printf("----------------------\n");
	printf("%.0lf\t%.0lf\t%.4lf\n",mediacomp/65,mediatroca/65,mediatemp/65);
}





