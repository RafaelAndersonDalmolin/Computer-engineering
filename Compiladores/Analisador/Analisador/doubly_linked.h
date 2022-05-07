#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
typedef struct _node {  // Cada nó possui armazena um valor e um ponteiro para o próximo.
	char* data;    
	int row;
    struct _node* next;
    struct _node* prev;
} node;

typedef struct {	// aponta para o primeiro nó na lista
    node* head; 
    node* tail;
    int size;
} list;
// Alocação/desalocação de memória
list* new_list();
void free_list(list* v);

// Funções de remoção de elementos
void list_pop_back(list* v);
void list_pop_front(list* v);
void list_erase(list* v,int i);

// Funções de inserção de elementos
void list_insert(list* v,char* data, int row, int i);
void list_push_back(list* v,char* data, int row);
void list_push_front(list* v,char* data, int row);

// Impressão do valores no vetor [0]...[size-1]
void list_print(list* v);
char* list_top(list* v);
char* list_front(list* v);
