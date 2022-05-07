#include"doubly_linked.h"
list* new_list(){      			   // Aloca memória para uma estrutura do tipo list, faz o head apontar para NULL	
	list* v = (list*) malloc(sizeof(list));
	v->size=0;
	v->head=NULL;
	v->tail=NULL;
	return v;
}
void free_list(list* v){		// libera a memoria de todos os nós e da lista	
	if(v->size!=0){
		node*n=v->head;
		node*x=0;
			while(n->next!=NULL)
			{
				x=n;
				n=n->next;
				free(x);
			}
			free(n);			
			free(v);
	}		
	else{
		free(v);
	}
}
void list_push_front(list* v, int value){ // inserir no inicio
	node* n=(node*) malloc(sizeof(node));
			if(v->size==0){		// lista esta vazia
				v->head=n;
				v->tail=n;
				n->next=NULL;
				n->prev=NULL;
				n->value=value;
				v->size++;				}
			else{               // lista com elementos
				n->next=v->head;
				n->prev=NULL;
				v->head->prev=n;
				v->head=n;
				n->value=value;
				v->size++;
			}
}
void list_push_back(list* v, int value){  //inserir no fim
	node* n=(node*) malloc(sizeof(node));
		if(v->size==0){		// lista esta vazia
			v->head=n;
			v->tail=n;
			n->next=NULL;
			n->prev=NULL;
			n->value=value;
			v->size++;
		}
		else{               // lista com elementos
			n->next=NULL;
			n->prev=v->tail;
			v->tail->next=n;
			v->tail=n;
			n->value=value;
			v->size++;
		}				
}
void list_insert(list* v, int value, int i){
	assert(i>=0 && i<=v->size);
			if(i==0){  // inserir no inicio
				list_push_front(v,value);
			}
			else{  // inserir em qualquer lugar entre a 0 e size/2 ou  entre size/2 ate size
			 assert(i>=0 && i<=v->size);
				if(i<(v->size/2)){ //inserir  entre a 0 e size/2.
					node* n=(node*) malloc(sizeof(node));					
					node*m=v->head;
					int pos=i;
					for(int i=0; i<pos; i++)
					{
						m=m->next;
					}
					n->next=m;
					n->prev=m->prev;
					m->prev=n;
					n->prev->next=n;
					n->value=value;
					v->size++;
				}
				else{			//inserir entre size/2 ate size
					if(i==v->size){ //verifica se nao cai na condiçao da posiçao que quer inserir ser a ultima
						list_push_back(v,value);
					}					
					else{	
						node* n=(node*) malloc(sizeof(node));				
						node*m=v->tail;
						int pos=i;
						for(int i=v->size-1; i>pos;	i--)
						{				
							m=m->prev;
						}
						n->next=m;
						n->prev=m->prev;
						m->prev=n;
						n->prev->next=n;
						n->value=value;
						v->size++;
					}
				}
			}
}
void list_print(list* v){ // imprimir a lista   [size] data[0] data[1] data[2] ... data[size-1] \n
	node* n=v->head;
	printf("[%d] ",v->size);
	while(n!=NULL){
		printf("%d ",n->value);
		n=n->next;
	}
	printf("\n");
}
void list_pop_back(list* v){
	assert(v->size!=0);	
		if(v->size==1){
			node*n=v->head;
			v->head=NULL;
			v->tail=NULL;
			free(n);
			v->size--;	
		}
		else{
			node*n=v->tail;
			v->tail=n->prev;
			v->tail->next=NULL;
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
			free(n);
			v->size--;	
		}
		else{
			node*n=v->head;
			v->head=n->next;
			v->head->prev=NULL;
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
					int pos=i;
					for(int i=0; i<pos; i++)
					{
						m=m->next;
					}
					m->prev->next=m->next;
					m->next->prev=m->prev;
					free(m);
					v->size--;
				}
				else{ //remover entre size/2 ate size
					if(i==v->size-1){ //verifica se nao cai na condiçao da posiçao que quer remover ser a ultima
						list_pop_back(v);
					}					
					else{				
						node*m=v->tail;
						int pos=i;
						for(int i=v->size-1; i>pos;	i--)
						{				
							m=m->prev;
						}
						m->prev->next=m->next;
						m->next->prev=m->prev;
						free(m);
						v->size--;
					}
				}
			}
}
void list_set(list* v, int pos, int value){
	assert(v->size!=0);	
		if(pos<(v->size/2)){ 
			node*m=v->head;
			for(int i=0; i<pos; i++)
			{
				m=m->next;
			}
			m->value=value;
		}
		else{
			node*m=v->tail;
			for(int i=v->size-1; i>pos;	i--)
			{				
				m=m->prev;
			}
			m->value=value;
		}
}
void reverse(list* a){
	if(a->size!=0 && a->size!=1){	
		node* n=a->tail;
		for(int i=a->size-1; i>0; i--)
		{
			list_push_back(a,n->value);
			list_erase(a,i);
			n=n->prev;
		}
		list_push_back(a,n->value);
		list_erase(a,0);
	}
}
