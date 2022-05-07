#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define EMPTY -1

typedef struct{
	long matricula;
	char nome[100];
} aluno;
int hashing(int item,int N){
	return item%N;
}
void hash_insert(aluno t[],int matricula,char NOME[],int N){
	int i=0; long a=matricula;
	int indice= hashing(matricula,N);
	while(t[indice].matricula!=EMPTY && i<N){				
		a++; i++;	
		indice= hashing(a,N);
	}
	if(t[indice].matricula==EMPTY){	
		t[indice].matricula=matricula;
		strcpy(t[indice].nome,NOME);
	}
}
void print_tabela(aluno t[],int N){
	for(int i=0; i<N; i++){
		printf("%d\t%ld\t%s\n", i, t[i].matricula, t[i].nome);
	}
}
int main(){
 	int N,A;	
	scanf("%d",&N); // tamanho da tabela, numero de alunos
	aluno t[N];
	for(int i=0; i<N; i++){
		t[i].matricula=EMPTY;
		strcpy(t[i].nome," ");
	}
	scanf("%d",&A);
	
	for(int i=0; i<A; i++){
		char a[100]; long ma;
		scanf("%ld %s",&ma,a);                 
        hash_insert(t,ma,a,N);

	}
	print_tabela(t,N);
}
