#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
typedef char type;	// variavel definida para facilitar na alteraçao do codigo
typedef struct {
    type* data;     // vetor do tipo type
    int size;       // tamanho atual do vetor
    int  capacity;  // tamanho reservado em memória 
} buffer;

buffer* new_buffer(void);  		// Aloca memória inicial para o vetor
void free_buffer(buffer* v); 	// Desaloca a memória do buffer	
void clear_buffer(buffer* v);   // Reinicializa o buffer
void buffer_resize(buffer* v);  // realloca memoria com o dobro do tamanho.
void buffer_insert(buffer*v,type value,int i);	//inserir no indice i
void buffer_push_back(buffer*v,type value);  	// inserir no final
void buffer_push_front(buffer* v,type value);   // inserir no inicio
type buffer_erase(buffer* v, int i);	//remove no indice i
type buffer_pop_back(buffer* v);		// retorna o valor na ultima posiçao
type buffer_pop_front(buffer* v); //retorna o valor na 1º posiçao
void buffer_print(buffer* v);	//imprime dados do buffer [size/capacity] data[0] data[1] data[2] ... data[size] \n
