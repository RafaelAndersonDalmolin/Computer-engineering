#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
typedef struct _node {
    int value;             // Valor armazenado
    struct _node* next;    // Endereço do próximo nó
}node;
typedef struct {
    node* head;
	int size;
}list;

list* new_list();        // Aloca memória inicial para o vetor
void free_list(list* l); // Desaloca a memória dos nodes e list.

						 // Funções de remoção de elementos
void list_pop_back(list* l);
void list_pop_front(list* l);
void list_erase(list* l, int i);

						// Funções de inserção de elementos
void list_insert(list* l, int value, int i);
void list_push_back(list* l, int value);
void list_push_front(list* l, int value);

node* list_at(list*l,int pos);		// retorna um ponteiro para nó
void list_set(list* v, int pos,int value); // Função de alteração de uma posição do vetor
bool list_empty(list* l);       
void list_print(list* l);
list* set_intersection(list* a, list* b);
void set_insert(list* l,int value);
list* set_union(list* a, list* b);
