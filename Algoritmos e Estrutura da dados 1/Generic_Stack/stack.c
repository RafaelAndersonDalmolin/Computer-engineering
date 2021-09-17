#include "stack.h"
stack* stack_new(void) {
    stack* s = vector_new();   // Alocação
    return s;
}
void stack_free(stack* s){                  // desalocação
    vector_free(s);
} 
void stack_push(stack* s,type value) {    // Inserçao
    vector_push_back(s, value);
}
type stack_pop(stack* s) {                 //remoção de elementos
    return vector_pop_back(s);
}
type stack_top(stack* s) {              // retorna um ponteiro para o topo da pilha
    return vector_get(s, s->size-1);
}
bool stack_empty(stack* s) {		// retorna verdadeiro se a pilha tiver vazia
    return s->size == 0; 
}
void stack_print(stack *s){	// imprime os elementos da pilha
	vector_print(s);
}
