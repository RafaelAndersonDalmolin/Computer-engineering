#include"classify.h"
bool id(char* str){
	if(isalpha(str[0])){
		int length =strlen(str);
		for(int i=1; i<length; i++){
			if(!(isalnum(str[i]))){
				return false;	
			}
		}
		return true;
	}
	else{
		return false;
	}
}

bool digit(char* str){
	int length=strlen(str);
	for(int i=0; i<length; i++){
		if(!(isdigit(str[i]))){
			return false;	
		}
	}
	return true;
}
int toreport(char* str){ // retorna false caso seja um ID invalido
	int length=strlen(str);
	if(isalpha(str[0])){
		return 1;
	}
	if(isdigit(str[0])){
		return -1;
	}
	return 0;
}
bool islexema(list* lista,char* str,int line){
	if(strcmp(str,"programa") == 0){
		list_push_back(lista,"PROG",line);
		return true;
	}
	else if(strcmp(str,"var") == 0){
		list_push_back(lista,"VAR",line);
		return true;
	}
	else if(strcmp(str,"inteiro") == 0){
		list_push_back(lista,"INT",line);
		return true;
	}
	else if(strcmp(str,"booleano") == 0){
		list_push_back(lista,"BOOL",line);
		return true;
	}
	else if(strcmp(str,"procedimento") == 0){
		list_push_back(lista,"PROC",line);
		return true;
	}
	else if(strcmp(str,"funcao") == 0){
		list_push_back(lista,"FUNC",line);
		return true;
	}
	else if(strcmp(str,"inicio") == 0){
		list_push_back(lista,"BEGIN",line);
		return true;
	}
	else if(strcmp(str,"fim") == 0){
		list_push_back(lista,"END",line);
		return true;
	}
	else if(strcmp(str,"se") == 0){
		list_push_back(lista,"IF",line);
		return true;
	}
	else if(strcmp(str,"entao") == 0){
		list_push_back(lista,"THEN",line);
		return true;
	}
	else if(strcmp(str,"senao") == 0){
		list_push_back(lista,"ELSE",line);
		return true;
	}
	else if(strcmp(str,"enquanto") == 0){
		list_push_back(lista,"WHILE",line);
		return true;
	}
	else if(strcmp(str,"faca") == 0){
		list_push_back(lista,"DO",line);
		return true;
	}
	else if(strcmp(str,"leia") == 0){
		list_push_back(lista,"READ",line);
		return true;
	}
	else if(strcmp(str,"escreva") == 0){
		list_push_back(lista,"WRITE",line);
		return true;
	}
	else if(strcmp(str,"verdadeiro") == 0){
		list_push_back(lista,"TRUE",line);
		return true;
	}
	else if(strcmp(str,"falso") == 0){
		list_push_back(lista,"FALSE",line);
		return true;
	}
	else if(strcmp(str,"nao") == 0){
		list_push_back(lista,"NOT",line);
		return true;
	}
	else if(strcmp(str,"ou") == 0){
		list_push_back(lista,"OR",line);
		return true;
	}
	else if(strcmp(str,"e") == 0){
		list_push_back(lista,"AND",line);
		return true;
	}
	else if(strcmp(str,":=") == 0){
		list_push_back(lista,"ATRIB",line);
		return true;
	}
	else if(strcmp(str,".") == 0){
		list_push_back(lista,"POINTFINAL",line);
		return true;
	}
	else if(strcmp(str,",") == 0){
		list_push_back(lista,"COMMA",line);
		return true;
	}
	else if(strcmp(str,":") == 0){
		list_push_back(lista,"TWOPOINT",line);
		return true;
	}
	else if(strcmp(str,";") == 0){
		list_push_back(lista,"POINTCOMMA",line);
		return true;
	}
	else if(strcmp(str,"+") == 0){
		list_push_back(lista,"ADD",line);
		return true;
	}
	else if(strcmp(str,"-") == 0){
		list_push_back(lista,"SUB",line);
		return true;
	}
	else if(strcmp(str,"*") == 0){
		list_push_back(lista,"MULT",line);
		return true;
	}
	else if(strcmp(str,"div") == 0){
		list_push_back(lista,"DIV",line);
		return true;
	}
	else if(strcmp(str,"(") == 0){
		list_push_back(lista,"PARE",line);
		return true;
	}
	else if(strcmp(str,")") == 0){
		list_push_back(lista,"PARD",line);
		return true;
	}
	else if(strcmp(str,"<>") == 0){
		list_push_back(lista,"DIFF",line);
		return true;
	}
	else if(strcmp(str,"=") == 0){
		list_push_back(lista,"EQUAL",line);
		return true;
	}
	else if(strcmp(str,"<") == 0){
		list_push_back(lista,"SMALL",line);
		return true;
	}
	else if(strcmp(str,">") == 0){
		list_push_back(lista,"BIGGER",line);
		return true;
	}
	else if(strcmp(str,"<=") == 0){
		list_push_back(lista,"SMALLEQUAL",line);
		return true;
	}
	else if(strcmp(str,">=") == 0){
		list_push_back(lista,"BIGGEREQUAL",line);
		return true;
	}
	else{ // verificar se é ID // Verificar se é DIGITO
		if(id(str)){
			list_push_back(lista,"ID",line);
			return true;
		}
		else if(digit(str)){
			list_push_back(lista,"NUM",line);
			return true;
		}
		else{
			return false;
		}
	}
}

