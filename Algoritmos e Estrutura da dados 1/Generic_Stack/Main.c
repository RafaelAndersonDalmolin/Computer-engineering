#include<stdio.h>
#include "stack.h"
int main(){
	stack *s; 
	s=stack_new(); // alocação
	stack_push(s,'R');
	stack_push(s,'A');
	stack_push(s,'F');
	stack_push(s,'A');
	stack_push(s,'E');
	stack_push(s,'L');
	stack_print(s);
	printf("Removeu -> %c\n",stack_pop(s));
	stack_print(s);
	printf("Top -> %c\n",stack_top(s));

	printf("Removeu -> %c\n",stack_pop(s));
	stack_print(s);
	printf("Topo -> %c\n",stack_top(s));

	printf("Removeu -> %c\n",stack_pop(s));
	stack_print(s);
	printf("Topo -> %c\n",stack_top(s));

	printf("Removeu -> %c\n",stack_pop(s));
	stack_print(s);
	printf("Topo -> %c\n",stack_top(s));

	printf("Removeu -> %c\n",stack_pop(s));
	stack_print(s);
	printf("Topo -> %c\n",stack_top(s));

	printf("Removeu -> %c\n",stack_pop(s));
	stack_print(s);
}
