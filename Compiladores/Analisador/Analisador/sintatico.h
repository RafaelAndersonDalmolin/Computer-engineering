#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"lexico.h" 
int hashing(char* str,int tamanho);
int indice(char* str);
list * analisador_sintatico(list * tokens);
