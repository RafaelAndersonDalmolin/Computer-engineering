#include"forward_list_dalmolin.h"

list* new_list(){      			   // Aloca memória para uma estrutura do tipo list, faz o head apontar para NULL	
	list* l = (list*) malloc(sizeof(list));
	l->size=0;
	l->head=NULL;
	return l;
}
void free_list(list* l){		// libera a memoria de todos os nós e da lista	
	if(l->size!=0){
		node*n=l->head;
		node*x=0;
			while(n->next!=NULL)
			{
				x=n;
				n=n->next;
				free(x);
			}
			free(n);			
			free(l);
	}		
	else{
		free(l);
	}
}
bool list_empty(list* l){	   // retorna 1 se a lista estiver vazia e 0 se estiver com algum nó.
	if(l->size==0)	
	 return 1;
	else
	 return 0;
}
void list_insert(list*l, int value, int i){      // inserir em qualquer lugar entre 0 e size.
	assert(i>=0 && i<=l->size);		
		if(i==0){
			list_push_front(l,value);
		}
		else{
			node*n =(node*)malloc(sizeof(node));
			node*x=list_at(l,i-1);
			n->next=x->next;
			x->next=n;
			n->value=value;
			l->size++;
		}
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
void list_push_back(list* l, int value){   // inserir no fim.
	node*n =(node*)malloc(sizeof(node));
		if(l->size==0){ // lista vazia
			l->head=n;
			n->next=NULL;
			n->value=value;
		}
		else{  //lista com elementos
			node*x=list_at(l,l->size-1);
			x->next=n;
			n->next=NULL;
			n->value=value;
		}
		l->size++;
}
void list_pop_back(list* l){  // remove no fim
	assert(l->size!=0);			
		list_erase(l,l->size-1);
}
void list_pop_front(list* l){  //remove no inicio
	assert(l->size!=0);	
		list_erase(l,0);
			
}
void list_erase(list* l, int i){   //remove em qualquer lugar
	assert(i>=0 && i<l->size && l->size!=0);		
		if(i==0){
			node*y=l->head;			
			l->head=y->next;
			free(y);
			l->size--;	
		}
		else{		
			node*x=list_at(l,i-1);
			node*y=x->next;	
			x->next=y->next;
			free(y);
			l->size--;
		}
}
void list_set(list* l, int pos, int value){	//troca o value na posiçao desejada
	node*n=list_at(l,pos);
	n->value=value;
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
void list_print(list* l){ // imprimir a lista   [size] data[0] data[1] data[2] ... data[size-1] \n
	node* n=l->head;
	printf("[%d] ",l->size);
	while(n!=NULL){
		printf("%d ",n->value);
		n=n->next;
	}
	printf("\n");
}

