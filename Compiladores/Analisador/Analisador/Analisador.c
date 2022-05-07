#include<stdio.h>
#include"sintatico.h"
void main (int argc, char *argv[ ] ){
	list* lista = analisador_lexico(argv[1]);
    if(lista != NULL){
		lista = analisador_sintatico(lista);
		if(lista != NULL){
			printf("\nENTRADA ACEITA\n");
		}
		else{
			printf("\nENTRADA REJEITADA\n");
		}
		//free_list(lista);
	}
}
