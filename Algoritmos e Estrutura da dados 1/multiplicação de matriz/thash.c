#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#define CAPACIDADE 1021
typedef struct _node {
    struct _node* next;    // Endereço do próximo nó
	int value;
	int i,j;
}node;
typedef struct {  // aponta para o primeiro nó na lista
    node* head;
	int size;
}list;
typedef struct{
	list** tabela;
	int linhas;
	int colunas;

}matrix;
list* new_list(){      			   // Aloca memória para uma estrutura do tipo list, faz o head apontar para NULL	
	list* l = (list*) malloc(sizeof(list));
	l->size=0;
	l->head=NULL;
	return l;
}
matrix* new_matrix(int N,int K){
	matrix* t=malloc(sizeof(matrix));
	t->linhas=N;
	t->colunas=K;	
	t->tabela=malloc(sizeof(list*)*N);  
	for(int i=0; i<N; i++){
		t->tabela[i]=new_list();
	}
	return t;
}
node* list_at(list*l,int COLUNA){	// retorna um ponteiro para nó na posiçao desejada.
	    node*atual=l->head;
		node*anterior=atual;
		while(atual!=NULL && (atual->j)<COLUNA){
			anterior=atual;
			atual=atual->next;
		}
		return anterior;
}
node* list_busca(list*l,int COLUNA){	// retorna um ponteiro para nó na posiçao desejada.
	    node*atual=l->head;
		while(atual!=NULL){
			if(atual->j==COLUNA){
				return atual;
			}
			atual=atual->next;
			
		}
		return NULL;
	
}
void list_insert(list* l,int LINHA,int COLUNA,int VALUE ){     
		if(l->head!=NULL){			// lista com elementos 
			node*aux=list_at(l,COLUNA);  // retorna o ponteiro de um nó com "j" maior ou menor que o que eu quero inserir
			if((aux->j)>COLUNA){			// inseri o elemento antes do nó retornado 
				node*n =(node*)malloc(sizeof(node));  
				n->next=aux;
				l->head=n;
				n->i=LINHA;
				n->j=COLUNA;
				n->value=VALUE;
				l->size++;
			}			
			if((aux->j)<COLUNA){		// inseri o elemento depois do nó retornado.
				node*n =(node*)malloc(sizeof(node));
				n->next=aux->next;
				aux->next=n;
				n->i=LINHA;
				n->j=COLUNA;
				n->value=VALUE;
				l->size++;
			}
		}
		else{ 		// lista estar vazia
			node*n =(node*)malloc(sizeof(node));
			l->head=n;
			n->next=NULL;
			n->i=LINHA;
			n->j=COLUNA;
			n->value=VALUE;
			l->size++;
		}
		
}
int hashing(int l,int N){
	return l%N;
}
void matrix_insert(matrix* t,int LINHA,int COLUNA,int VALUE){  	
	int indice=hashing(LINHA,t->linhas);
	node*aux=list_busca(t->tabela[indice],COLUNA);
	if(aux!=NULL){
		aux->value=VALUE;
	}
	else{
		list_insert(t->tabela[indice],LINHA,COLUNA,VALUE);
	}
}
void list_print(list* l,int linhas,int colunas){
	node* n=l->head;
	while(n!=NULL){
		printf("%d %d %d\n",n->i,n->j,n->value);
		n=n->next;
	}
}
void print_matrix(matrix* t){
	int N=t->linhas;
	int indice;	
	for(int i=0; i<N; i++){
		indice=hashing(i,t->linhas);
		list_print(t->tabela[indice],t->linhas,t->colunas);
	}
	printf("\n");
}
int buscai(matrix* A,int i,int j){
	int indicel=hashing(i,A->linhas);	
	node* n=A->tabela[indicel]->head;
	while(n!=NULL){		
		if((n->j)==j){		
			return n->value;
		}	
		n=n->next; 	
		if(n==NULL){
			return 0;
		}	
	}
	return 0;
}
int buscaj(matrix* A,int i,int j){
	int indicel=hashing(i,A->linhas);	
	node* n=A->tabela[indicel]->head;
	while(n!=NULL){		
		if((n->j)==j){	
			return n->value;
		}	
		n=n->next; 
		if(n==NULL){
			return 0;
		}	
	}
	return 0;
}
matrix* multiplica(matrix* A, matrix* B){
	matrix* C=new_matrix(A->linhas,B->colunas); 
	int soma=0; int valueA; int valueB;
	for(int i=0; i<(A->linhas); i++){	// pegando primeira linha e assim por diante		

		for(int t=0; t<(B->colunas); t++){
    	
			for(int j=0; j<(A->colunas); j++){

				valueA=buscai(A,i,j);
				valueB=buscaj(B,j,t);

				soma=soma+(valueA*valueB);				
			} 
			if(soma!=0){
				matrix_insert(C,i,t,soma);
				valueA=0;
				valueB=0;
				soma=0;
			}
		}
	}
	return C;
}
int main (){
	int LINHAS,COLUNAS,value,P,linha,coluna;
	scanf("%d %d",&LINHAS,&COLUNAS);
	matrix* a=new_matrix(LINHAS,COLUNAS); 
	scanf("%d",&P);
	for(int i=0; i<P; i++){
		scanf("%d %d %d",&linha,&coluna,&value);
		matrix_insert(a,linha,coluna,value);
	}
	scanf("%d %d",&LINHAS,&COLUNAS);
	matrix* b=new_matrix(LINHAS,COLUNAS);
	scanf("%d",&P);
	for(int i=0; i<P; i++){
		scanf("%d %d %d",&linha,&coluna,&value);
		matrix_insert(b,linha,coluna,value);
	}
	//print_matrix(a);
	//print_matrix(b);
	matrix* nova=multiplica(a,b);
	print_matrix(nova);
}
