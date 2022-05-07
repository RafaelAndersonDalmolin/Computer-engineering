#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
typedef struct _node {
    struct _node* next;    // Endereço do próximo nó
	long matricula;
	char nome[100];;
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
node* list_at(list*l,int pos){	// retorna um ponteiro para nó na posiçao desejada.
	assert(pos>=0 && pos<l->size);
		node*n=l->head;
		for(int i=0; i<pos; i++)
		{
			n=n->next;
		}
		return n;
}
void list_push_back(list* l,long matricula,char* NOME){   // inserir no fim.
	node*n =(node*)malloc(sizeof(node));
		if(l->size==0){ // lista vazia
			l->head=n;
			n->next=NULL;
			n->matricula=matricula;
			strcpy(n->nome,NOME);
			
		}
		else{  //lista com elementos
			node*x=list_at(l,l->size-1);
			x->next=n;
			n->next=NULL;
			n->matricula=matricula;
			strcpy(n->nome,NOME);
		}
		l->size++;
}
int hashing(int chave,int N){
	return chave%N;
}
void hash_insert(hashset* t,int matricula,char* NOME){  
	int indice=hashing(matricula,t->tamanho);
	list_push_back(t->tabela[indice],matricula,NOME);
}

void list_print(list* l){ // imprimir a lista  
	node* n=l->head;
	if(n==NULL){
		printf(" ");
	}
	while(n!=NULL){
		printf("%s",n->nome);
		n=n->next; 
		if(n!=NULL){
			printf(", ");
		}
	}
	printf("\n");
}
void print_hash(hashset* t,int N){
	for(int i=0; i<N; i++){
		printf("%d:",i);
		list_print(t->tabela[i]);
	}
}
int main (){
	int N;
	scanf("%d",&N); // tamanho da tabela
	hashset* tab=new_hash(N);
	int A;  // numero de elementos a serem inseridos
	scanf("%d",&A);
	for(int i=0; i<A; i++){
		char a[100]; long ma;
		scanf("%ld %s",&ma,a);                 
        hash_insert(tab,ma,a);
		
	}	
	print_hash(tab,N);
}










 
