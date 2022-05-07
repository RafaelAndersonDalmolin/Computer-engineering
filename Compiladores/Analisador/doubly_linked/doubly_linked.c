#include"doubly_linked.h"
list* new_list(){      			   // Aloca memória para uma estrutura do tipo list, faz o head apontar para NULL	
	list* v = (list*) malloc(sizeof(list));
	v->size=0;
	v->head=NULL;
	v->tail=NULL;
	return v;
}
void free_list(list* v){		// libera a memoria de todos os nós e seus elementos e da lista	
	if(v->size!=0){
		node*n=v->head;
		node*x;
		while(n->next!=NULL){
			x=n;
			n=n->next;
			free(x->data);
			free(x);
		}
		free(n->data);
		free(n);			
		free(v);
	}		
	else{
		free(v);
	}
}
void list_push_front(list* v,char* data,int row){ // inserir no inicio
	node* n=(node*) malloc(sizeof(node));
	n->data=(char*) malloc(sizeof(char)*(strlen(data)+1));
	if(v->size==0){		// lista esta vazia
		v->head=n;
		v->tail=n;
		n->next=NULL;
		n->prev=NULL;
		n->row=row;
		strcpy(n->data,data);
		v->size++;				}
	else{               // lista com elementos
		n->next=v->head;
		n->prev=NULL;
		v->head->prev=n;
		v->head=n;
		n->row=row;
		strcpy(n->data,data);
		v->size++;
	}
}
void list_push_back(list* v,char* data,int row){  //inserir no fim
	node* n=(node*) malloc(sizeof(node));
	n->data=(char*) malloc(sizeof(char)*(strlen(data)+1));
	if(v->size==0){		// lista esta vazia
		v->head=n;
		v->tail=n;
		n->next=NULL;
		n->prev=NULL;
		n->row=row;
		strcpy(n->data,data);
		v->size++;
	}
	else{               // lista com elementos
		n->next=NULL;
		n->prev=v->tail;
		v->tail->next=n;
		v->tail=n;
		n->row=row;
		strcpy(n->data,data);
		v->size++;
	}				
}
void list_insert(list* v,char* data,int row, int i){
	assert(i>=0 && i<=v->size);
		if(i==0){  // inserir no inicio
			list_push_front(v,data,row);
		}
		else{  // inserir em qualquer lugar entre a 0 e size/2 ou  entre size/2 ate size
			assert(i>=0 && i<=v->size);
				if(i<(v->size/2)){ //inserir  entre a 0 e size/2.
					node* n=(node*) malloc(sizeof(node));		
					n->data=(char*) malloc(sizeof(char)*(strlen(data)+1));			
					node*m=v->head;
					for(int j=0; j<i; j++)
					{
						m=m->next;
					}
					n->next=m;
					n->prev=m->prev;
					m->prev=n;
					n->prev->next=n;
					n->row=row;
					strcpy(n->data,data);
					v->size++;
				}
				else{			//inserir entre size/2 ate size
					if(i==v->size){ //verifica se nao cai na condiçao da posiçao que quer inserir ser a ultima
						list_push_back(v,data,row);
					}					
					else{	
						node* n=(node*) malloc(sizeof(node));
						n->data=(char*) malloc(sizeof(char)*(strlen(data)+1));				
						node*m=v->tail;
						for(int j=v->size-1; j>i; j--)
						{				
							m=m->prev;
						}
						n->next=m;
						n->prev=m->prev;
						m->prev=n;
						n->prev->next=n;
						n->row=row;
						strcpy(n->data,data);
						v->size++;
					}
				}
		}
}
void list_print(list* v){ // imprimir a lista   [size] data[0] data[1] data[2] ... data[size-1] \n
	node* n=v->head;
	printf("SIZE:%d\n",v->size);
	while(n!=NULL){
		printf("<%s,%d>",n->data,n->row);
		n=n->next;
		printf("\n");
	}
}
void list_pop_back(list* v){
	assert(v->size!=0);	
		if(v->size==1){
			node*n=v->head;
			v->head=NULL;
			v->tail=NULL;
			free(n->data);
			free(n);
			v->size--;	
		}
		else{
			node*n=v->tail;
			v->tail=n->prev;
			v->tail->next=NULL;
			free(n->data);
			free(n);		
			v->size--;
		}				
}
void list_pop_front(list* v){
	assert(v->size!=0);
		if(v->size==1){
			node*n=v->head;
			v->head=NULL;
			v->tail=NULL;
			free(n->data);
			free(n);
			v->size--;	
		}
		else{
			node*n=v->head;
			v->head=n->next;
			v->head->prev=NULL;
			free(n->data);
			free(n);		
			v->size--;
		}					
}
void list_erase(list* v, int i){
	assert(i>=0 && i<v->size && v->size!=0);
		if(i==0){  //remover no inicio
			list_pop_front(v);
		}
		else{  // remover em qualquer lugar entre a 0 e size/2 ou  entre size/2 ate size
				if(i<(v->size/2)){ //remover  entre a 0 e size/2.				
					node*m=v->head;
					for(int j=0; j<i; j++)
					{
						m=m->next;
					}
					m->prev->next=m->next;
					m->next->prev=m->prev;
					free(m->data);
					free(m);
					v->size--;
				}
				else{ //remover entre size/2 ate size
					if(i==v->size-1){ //verifica se nao cai na condiçao da posiçao que quer remover ser a ultima
						list_pop_back(v);
					}					
					else{				
						node*m=v->tail;
						for(int j=v->size-1; j>i;	j--)
						{				
							m=m->prev;
						}
						m->prev->next=m->next;
						m->next->prev=m->prev;
						free(m->data);
						free(m);
						v->size--;
					}
				}
		}
}
