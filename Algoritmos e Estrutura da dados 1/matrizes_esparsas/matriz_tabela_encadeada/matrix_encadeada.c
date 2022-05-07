#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#define CAPACIDADE 1021
typedef struct _node {
    struct _node* up;      // endereço do nó de cima
	struct _node* below;   // endereço do nó de baixo
	struct _node* next;    // Endereço do nó a frente
    struct _node* prev;		// Endereço do nó a baixo
	int value;
	int i,j;
}node;
typedef struct {	// aponta para o primeiro nó na lista
    node* head; 
    node* tail;
    int size;
} list;
typedef struct{
	list** vetrow;
	list** vetcol;
	int linhas;
	int colunas;

}matrix;
list* new_list(){      			   // Aloca memória para uma estrutura do tipo list, faz o head apontar para NULL	
	list* v = (list*) malloc(sizeof(list));
	v->size=0;
	v->head=NULL;
	v->tail=NULL;
	return v;
}
matrix* new_matrix(int N,int K){
	matrix* t=malloc(sizeof(matrix));
	t->linhas=N;
	t->colunas=K;	
	t->vetrow=malloc(sizeof(list*)*N);  
	for(int i=0; i<N; i++){
		t->vetrow[i]=new_list();
	}
	t->vetcol=malloc(sizeof(list*)*K);  
	for(int i=0; i<K; i++){
		t->vetcol[i]=new_list();
	}
	return t;
}
node* list_buscalinha(list*l,int a){	
	    node*n=l->head;
		while(n!=NULL){
			if((n->j)==a){
				return n;
			}
			n=n->next;
		}
	return NULL;
}
int hashing(int l,int N){
	return l%N;
}
node* list_maiorlinha(list* l,int a){
	node* aux=l->head;
	for(int i=0; i<l->size; i++){
		if((aux->j)>a){
			return aux;
		}
		aux=aux->next;	
	}
	return NULL;
}
void list_insertlinha(matrix *t,int LINHA,int COLUNA,int VALUE ){     
	int indicel=hashing(LINHA,t->linhas);		
		if(t->vetrow[indicel]->size==0){    // a lista esta vazia, só inserir o elemento no primeiro lugar
			node* novo=malloc(sizeof(node));
			t->vetrow[indicel]->tail=novo;
			t->vetrow[indicel]->head=novo;
			t->vetrow[indicel]->size++;
			novo->next=NULL;
			novo->prev=NULL;
			novo->i=LINHA;
			novo->j=COLUNA; 
			novo->value=VALUE;
			
			return;
		}
		else{
			node* aux=list_buscalinha(t->vetrow[indicel],COLUNA);
			if(aux!=NULL){ 
				aux->value=VALUE; 
				return;
			}
			else{
				aux=list_maiorlinha(t->vetrow[indicel],COLUNA);  // retorna um elemento com i maior ou retorna null caso nao tenha
				if(aux!=NULL){    // retornou um elemento com i maior
					if(aux==t->vetrow[indicel]->head){    // verificar se o elemento é o inicio da lista
						node* novo=malloc(sizeof(node));
						novo->next=aux;
						novo->prev=aux->up;
						aux->prev=novo;
						t->vetrow[indicel]->head=novo;
						novo->i=LINHA;
						novo->j=COLUNA;
						novo->value=VALUE;
						t->vetrow[indicel]->size++;
						return;
					}
					else{           //elemento maior esta em qualquer lugar da lista podendo estar no meio ou no fim;
						node* novo=malloc(sizeof(node));
						novo->next=aux;
						novo->prev=aux->up;
						novo->prev->next=novo;
						aux->prev=novo;
						novo->i=LINHA;
						novo->j=COLUNA;
						novo->value=VALUE;
						t->vetrow[indicel]->size++; 
						return;
					}
				}
				else{     // nao ha nenhum elemento maior na lista, entao vou inserir o meu que é maior no final
					node* novo=malloc(sizeof(node));
					t->vetrow[indicel]->tail->next=novo;
					novo->prev=t->vetrow[indicel]->tail;
					novo->next=NULL;
					t->vetrow[indicel]->tail=novo;
					novo->i=LINHA;
					novo->j=COLUNA;
					novo->value=VALUE;
					t->vetrow[indicel]->size++;  
					return;
				}
			}
		}	
}
node* list_buscacoluna(list*l,int a){	
	    node*n=l->head;
		while(n!=NULL){
			if((n->i)==a){
				return n;
			}
			n=n->below;
		}
	return NULL;
}
node* list_maiorcoluna(list* l,int a){
	node* aux=l->head;
	for(int i=0; i<l->size; i++){
		if((aux->i)>a){
			return aux;
		}
		aux=aux->below;	
	}
	return NULL;
}
void list_insertcoluna(matrix *t,int LINHA,int COLUNA,int VALUE ){     
	int indicec=hashing(COLUNA,t->colunas);		
		if(t->vetcol[indicec]->size==0){    // a lista esta vazia, só inserir o elemento no primeiro lugar
			node* novo=malloc(sizeof(node));
			t->vetcol[indicec]->tail=novo;
			t->vetcol[indicec]->head=novo;
			t->vetcol[indicec]->size++;
			novo->below=NULL;
			novo->up=NULL;
			novo->i=LINHA;
			novo->j=COLUNA; 
			novo->value=VALUE;
			
			return;
		}
		else{
			node* aux=list_buscacoluna(t->vetcol[indicec],LINHA);
			if(aux!=NULL){ 
				aux->value=VALUE; 
				return;
			}
			else{
				aux=list_maiorcoluna(t->vetcol[indicec],LINHA);  // retorna um elemento com i maior ou retorna null caso nao tenha
				if(aux!=NULL){    // retornou um elemento com i maior
					if(aux==t->vetcol[indicec]->head){    // verificar se o elemento é o inicio da lista
						node* novo=malloc(sizeof(node));
						novo->below=aux;
						novo->up=aux->up;
						aux->up=novo;
						t->vetcol[indicec]->head=novo;
						novo->i=LINHA;
						novo->j=COLUNA;
						novo->value=VALUE;
						t->vetcol[indicec]->size++;
						return;
					}
					else{           //elemento maior esta em qualquer lugar da lista podendo estar no meio ou no fim;
						node* novo=malloc(sizeof(node));
						novo->below=aux;
						novo->up=aux->up;
						novo->up->below=novo;
						aux->up=novo;
						novo->i=LINHA;
						novo->j=COLUNA;
						novo->value=VALUE;
						t->vetcol[indicec]->size++; 
						return;
					}
				}
				else{     // nao ha nenhum elemento maior na lista, entao vou inserir o meu que é maior no final
					node* novo=malloc(sizeof(node));
					t->vetcol[indicec]->tail->below=novo;
					novo->up=t->vetcol[indicec]->tail;
					novo->below=NULL;
					t->vetcol[indicec]->tail=novo;
					novo->i=LINHA;
					novo->j=COLUNA;
					novo->value=VALUE;
					t->vetcol[indicec]->size++;  
					return;
				}
			}
		}	
}
void matrix_insert(matrix* t,int LINHA,int COLUNA,int VALUE){  	
		list_insertlinha(t,LINHA,COLUNA,VALUE);
		list_insertcoluna(t,LINHA,COLUNA,VALUE);
}
void list_print(list* l,int linhas,int colunas){
	node* n=l->head;
	if(n!=NULL){
		for(int contador=0; contador<colunas; contador++){	
			if(n!=NULL && (n->j)==contador){
				printf("%4d",n->value);
				n=n->next;
			}
			else{
				printf("%4d",0);
			}	
		}
	}
	else{
		for(int i=0; i<colunas; i++){
			printf("%4d",0);
		}
		
	}
	printf("\n");	

}
void print_matrix(matrix* t){
	int N=t->linhas;
	int indice;	
	for(int i=0; i<N; i++){
		indice=hashing(i,t->linhas);
		list_print(t->vetrow[indice],t->linhas,t->colunas);
	}
	printf("\n");


}
int buscai(matrix* A,int i,int j){
	int indicel=hashing(i,A->linhas);	
	node* n=A->vetrow[indicel]->head;
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
	int indicec=hashing(i,A->colunas);	
	node* n=A->vetcol[indicec]->head;
	while(n!=NULL){		
		if((n->i)==j){	
			return n->value;
		}	
		n=n->below; 
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
				valueB=buscaj(B,t,j);

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
	print_matrix(a);
	print_matrix(b);
	matrix* nova=multiplica(a,b);
	print_matrix(nova);

}
