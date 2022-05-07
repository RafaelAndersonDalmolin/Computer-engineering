#include"lexico.h"

list * analisador_lexico(char* str){

	FILE *file = fopen(str, "r"); // Recebe como argumanto na linha de comando o nome do arquivo de texto
	if (!file) { // Encerra o programa caso nao consiga abrir o arquivo passado
	printf("Could not open file!\n");
	exit(-1);
	}
	char c;
	int lineword,line=1,error=9999; 
	bool write=true; 
	buffer* word=new_buffer();
	list* lista = new_list();

	while((c=fgetc(file)) != EOF){ // pega caractere por caractere escrito no arquivo de texto
		if(c=='\n'){	// Caso o caractere seja um quebra linha contamos para saber em qual linha estamos lendo no texto
			line++;
		}
		if(c=='{' && write){ // Caso o caractere do texto seja uma chave, desabilita a escrita na pilha
			write=false;
		}
		if(write && !(isspace(c))){ // se a escrita esta habilitada e o caractere lido é um caractere nao nulo
			buffer_push_back(word,c); // gravamos na pilha e salvamos qual a linha atual do caractere gravado
			lineword=line;
		}
		if((word->size) > 0 && (isspace(c) || c == EOF)){// caso o caractere lido seja nulo, entao verificamos se existe uma palavra na pilha
			buffer_push_back(word,'\0'); //inserimos um fim de string, e classificamos a palavra encontrada
			if(!(islexema(lista,word->data,lineword))){// se a palavra for classificada como tokens guardamos ela na lista
				error = toreport(word->data);//se a palavra nao for lexema, classificamos o tipo de erro lexico
				if(error == 1){
					printf("Erro linha %d: Identificador invalido\n",lineword);
				}
				else if(error ==-1){
					printf("Erro linha %d: Numero invalido\n",lineword);
				}
				else{
					printf("Erro linha %d: Caractere nao reconhecido\n",lineword);
				}
			}
			clear_buffer(word); // limpa a pilha para começar a escrever uma nova palavra
		}
		if(c=='}' && !write){  // Caso o caractere do texto seja uma chave, Habilita a escrita na pilha
			write=true;
		}		
	}
	fclose(file);
	free_buffer(word);
	if(error != 9999){
		free_list(lista);
		return NULL;
	}
	else{
		return lista;
	}
	
}
