#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#define CAPACIDADE 1021
typedef struct _node {
    struct _node* next;    // Endereço do próximo nó
	int value;
}node;
typedef struct {  // aponta para o primeiro nó na lista
    node* head;
	int size;
}list;
typedef struct{
	list** tabela;
	int tamanho;

}hashset;
list* new_list(){      			   // Aloca memória para uma estrutura do tipo list, faz o head apontar para NULL	
	list* l = (list*) malloc(sizeof(list));
	l->size=0;
	l->head=NULL;
	return l;
}
hashset* new_hash(int N){
	hashset* t=malloc(sizeof(hashset));
	t->tamanho=N;	
	t->tabela=malloc(sizeof(list*)*N);  
	for(int i=0; i<N; i++){
		t->tabela[i]=new_list();
	}
	return t;
}
int hashing(int chave,int N){
	return chave%N;
}
int search_list(list*l,long elem){
	node* n=l->head;
	while(n!=NULL){
		if(n->value==elem){
			return 1;
		}
		n=n->next; 
	}
	return 0;
}
int search_hash(hashset* t,long elem){
	int indice=hashing(elem,t->tamanho);
	return search_list(t->tabela[indice],elem);
}
void list_push_front(list* l, int value){  // inserir no inicio.		
	node*n =(node*)malloc(sizeof(node));
	if(l->size==0){  // lista vazia
		l->head=n;			
		n->next=NULL;
		n->value=value;
	}
	else{   // lista com elementos
		n->next=l->head;
		l->head=n;
		n->value=value;
	}
	l->size++;
}
void hash_insert(hashset* t,long elem){  
	if(search_hash(t,elem)==0){
		int indice=hashing(elem,t->tamanho);
		list_push_front(t->tabela[indice],elem);
	}
}
void list_print(list* l){ // imprimir a lista   [size] data[0] data[1] data[2] ... data[size-1] \n
	node* n=l->head;
	while(n!=NULL){
		printf("%d ",n->value);
		n=n->next;
	}
}
void print_hash(hashset* t){
	int N=t->tamanho;	
	for(int i=0; i<N; i++){
		list_print(t->tabela[i]);
	}
	printf("\n");
}

int main (){
	hashset* tab=new_hash(CAPACIDADE);
	int A;  // numero de elementos a serem inseridos
	scanf("%d",&A);
	for(int i=0; i<A; i++){
		long elem;
		scanf("%ld",&elem);                 
        hash_insert(tab,elem);
		
	}	
	print_hash(tab);
}
