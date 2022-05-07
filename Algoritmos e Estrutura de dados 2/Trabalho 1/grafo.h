#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<time.h>
#include<unistd.h> 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct _node {       // Estruturas
    int vertex;            
		struct _edge* head; 
		struct _edge* tail;
		struct _node* up; 
		struct _node* bellow;
		int size;    
}node;
typedef struct _edge{
    int vertex;           
		struct _edge* prev;  
    struct _edge* next;    
}edge;
typedef struct{
    node* head;
		node* tail;
		int size;
}grafo;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
grafo* new_grafo();       //Aloca memoria para um grafo      OK
void free_grafo(grafo *g);//desaloca memoria e apaga o grafo  OK

void insert_vertex(grafo* g,int value);	//funçoes de insersao de elementos		OK
void insert_edge(grafo* g,int v,int a);	//										OK
void new_edge(node* n,int v);//													OK
void new_vertex(grafo* g,int value);//											OK

void remove_vertex(grafo*g,int v); //funçoes de remoçao de elementos 			OK
void remove_edge(grafo* g,int v,int a);//										OK
void r_edge(node* n,edge* e);//													OK
void r_vertex(grafo* g,node* n);//												OK


bool exist_vertex(grafo* g,int v); //funçoes de verificaçao		OK
bool exist_edge(node* v,int e);		//							OK

edge* search_edge(node* v,int e);   //funçoes de busca			OK
node* search_vertex(grafo* g,int v);//							OK

void print_grafo(grafo* g); //imprimir o grafo					OK
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




