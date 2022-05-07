#include<ctype.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"doubly_linked.h"
bool islexema(list* lista,char* str,int line);	// reconhece se é um lexema
bool id(char* str);			// retorna se é um identificador valido
bool digit(char* str);		// retorna se é um numero valido
int toreport(char* str);	// retorna 0 se caractere nao reconhecido,1 se indentificador invalido,-1 se numero invalido
