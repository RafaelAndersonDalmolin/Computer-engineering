#include"buffer.h"
buffer* new_buffer(void){  // Aloca memória inicial para o vetor
	buffer* v=malloc(sizeof(buffer));
	v->data=malloc(sizeof(type)*4);
	v->size=0;
	v->capacity=4;
	return v;
}
void free_buffer(buffer* v){ // Desaloca a memória do buffer.		 			
	free(v->data);	   
	free(v);   		
}
void clear_buffer(buffer* v){
	v->size=0;
}
void buffer_resize(buffer* v){  // realloca memoria com o dobro do tamanho.		
	v->capacity *=2;	
	v->data=realloc (v->data,sizeof(type)*v->capacity);

}

void buffer_insert(buffer*v,type value,int i){ 
	assert(i >= 0 && i<=v->size);       // verifica se o i onde a pessoa quer inserir nao esta fora do size
	if(v->size == v->capacity){	    //verifica se o size nao esta do tamanho da capacidade, caso esteja dobra a capacidade;
		buffer_resize(v);
	}	
	for(int size=v->size; i<size; size--){ // arrasta todos os itens para a direita e inseri no lugar desejado
		v->data[size]=v->data[size-1];
	}
	v->data[i]=value;
	v->size++;				// apos arrastar e inserir altera o size para a ultima posiçao livre
}

void buffer_push_back(buffer*v,type value){  	// inserir no final
	buffer_insert(v,value,v->size);
}
void buffer_push_front(buffer* v,type value){   // inserir no inicio
	buffer_insert(v,value,0);
}

type buffer_erase(buffer* v, int i){		// salva o valor na posiçao i e arrasta todas para a esquerda ate size-1
    assert(i >= 0 && i<=v->size);		// verifica se o i onde a pessoa quer remover nao esta fora do size;
	type x=v->data[i];
	v->size--;
	for(;i<v->size; i++){
	   v->data[i]=v->data[i+1];
	}
	v->data[v->size]='\0';
	return x;
}
type buffer_pop_back(buffer* v){		// retorna o valor na ultima posiçao do vetor, remove o ultimo valor e altera o size
	return buffer_erase(v,v->size-1);
}
type buffer_pop_front(buffer* v){ //retorna o valor na 1º posiçao, move tudo para a esquerda e altera o size
	return buffer_erase(v,0);
}
void buffer_print(buffer* v){	// [size/capacity] data[0] data[1] data[2] ... data[size] \n
        
	printf("[%d/%d] ",v->size,v->capacity);   
	for(int i=0; i<v->size; i++)
	    printf("[%c]",v->data[i]);
	
	printf("\n");
}
