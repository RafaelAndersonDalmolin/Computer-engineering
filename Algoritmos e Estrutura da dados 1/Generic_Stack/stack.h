#ifndef _STACK_H_
#define _STACK_H_
#include "vector.h"
#include <stdbool.h>
typedef vector stack;

stack* stack_new();			// alocação 
void stack_free(stack* s);	//desalocaçao

type stack_pop(stack* s);				//remoçao de elementos     
void stack_push(stack* s,type value);	//inserçao

type stack_top(stack* s);	//Observar o topo da pilha, sem remover
bool stack_empty(stack* s);	// verificar se a pilha esta vazia
void stack_print(stack *s); // imprime os elementos da pilha
#endif
