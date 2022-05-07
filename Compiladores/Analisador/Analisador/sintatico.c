#include"sintatico.h"
int hashing(char* str,int tamanho){
	int length = strlen(str),cod=0,aux=0;
	for(int i=0; i< length; i++){
		aux= (int) str[i];
		cod += aux;
	}
	return cod%tamanho;
}
int indice(char* str){
	char* strings [1][39]={"AND","ATRIB","ADD","BIGGER","BIGGEREQUAL","BOOL","BEGIN","COMMA","DIFF","DO",
	"DIV","ELSE","END","EQUAL","FUNC","FALSE","INT","IF","ID","MULT",
	"NUM","NOT","OR","POINTCOMMA","PROC","PROG","POINTFINAL","PARE","PARD","READ",
	"SMALL","SMALLEQUAL","SUB","THEN","TWOPOINT","TRUE","VAR","WHILE","WRITE"};
	for(int i=0; i<39; i++){
		if(strcmp(str,strings[0][i]) == 0){
			return i;	
		}
	}
}
list* analisador_sintatico(list* tokens){
  	char* matrix[26][39];
	for (int i=0; i<26; i++){
		for(int j=0; j<39; j++){
			matrix[i][j] = "@";
		}
	}
	matrix[13][25] =" PROG ID POINTCOMMA B POINTFINAL";
	matrix[14][6] = " BEGIN P N";
	matrix[14][36] = " D C";
	matrix[14][24] = " I M";
	matrix[14][14] = " I M";
	matrix[15][6] = " M";
	matrix[15][24] = " I M";
	matrix[15][14] = " I M";
	matrix[16][36] = " VAR F POINTCOMMA E";
	matrix[17][18] = " F POINTCOMMA E";
	matrix[17][6] = "#";
	matrix[17][24] = "#";
	matrix[17][14] = "#";  
	matrix[18][18] = " ID G TWOPOINT H";
	matrix[19][7] = " COMMA ID G";
	matrix[19][34] = "#";
	matrix[20][16] = " INT";
	matrix[20][5] = " BOOL";
	matrix[21][24] = " K POINTCOMMA J";
	matrix[21][14] = " L POINTCOMMA J";
	matrix[22][24] = " I";
	matrix[22][14] = " I";
	matrix[22][6] = "#";
	matrix[23][24] = " PROC ID POINTCOMMA B";
	matrix[24][14] = " FUNC ID TWOPOINT H POINTCOMMA B";
	matrix[25][6] = " BEGIN P N";
	matrix[0][23] = " POINTCOMMA O";
	matrix[0][12] = " END";
	matrix[1][18] = " P N";
	matrix[1][17] = " P N";
	matrix[1][37] = " P N";
	matrix[1][29] = " P N";
	matrix[1][38] = " P N";
	matrix[1][6] = " P N";
	matrix[1][12] = " END";
	matrix[2][18] = " ID Q";
	matrix[2][17] = " IF S THEN P R";
	matrix[2][37] = " WHILE S DO P"; 
	matrix[2][29] = " READ PARE ID PARD";
	matrix[2][38] = " WRITE PARE ID PARD";
	matrix[2][6] = " BEGIN P N";
	matrix[3][1] = " ATRIB S";
	matrix[3][11] = "#";
	matrix[3][23] = "#";
	matrix[3][12] = "#";
	//matrix[4][11] = " ELSE P"; // tratar conflito da tabela
	//matrix[4][11] = "#";
	matrix[4][23] = "#";
	matrix[4][12] = "#";
	matrix[5][2] = " V T";
	matrix[5][32] = " V T";
	matrix[5][20] = " V T";
	matrix[5][18] = " V T";
	matrix[5][27] = " V T";
	matrix[5][35] = " V T";
	matrix[5][15] = " V T";
	matrix[5][21] = " V T";
	matrix[6][8] = " U V";
	matrix[6][13] = " U V";
	matrix[6][30] = " U V";
	matrix[6][31] = " U V";
	matrix[6][3] = " U V";
	matrix[6][4] = " U V";
	matrix[6][28] = "#";
	matrix[6][33] = "#";
	matrix[6][9] = "#";
	matrix[6][11] = "#";
	matrix[6][23] = "#";
	matrix[6][12] = "#"; 
	matrix[7][8] = " DIFF";
	matrix[7][13] = " EQUAL";
	matrix[7][30] = " SMALL";
	matrix[7][31] = " SMALLEQUAL";
	matrix[7][3] = " BIGGER";
	matrix[7][4] = " BIGGEREQUAL";
	matrix[8][2] = " ADD W X";
	matrix[8][32] = " SUB W X";
	matrix[8][20] = " W X";
	matrix[8][18] = " W X";
	matrix[8][27] = " W X";
	matrix[8][35] = " W X";
	matrix[8][15] = " W X";
	matrix[8][21] = " W X";
	matrix[10][2] = " ADD W X"; 
	matrix[10][32] = " SUB W X";
	matrix[10][22] = " OR W X";
	matrix[10][8] = "#";
	matrix[10][13] = "#";
	matrix[10][30] = "#";
	matrix[10][31] = "#";
	matrix[10][3] = "#";
	matrix[10][4] = "#";
	matrix[10][28] = "#";
	matrix[10][33] = "#";
	matrix[10][9] = "#";
	matrix[10][11] = "#";
	matrix[10][23] = "#";
	matrix[10][0] = "#";
	matrix[9][20] = " Z Y";
	matrix[9][18] = " Z Y";
	matrix[9][27] = " Z Y";
	matrix[9][35] = " Z Y";
	matrix[9][15] = " Z Y";
	matrix[9][21] = " Z Y";
	matrix[11][19] = " MULT Z Y";
	matrix[11][10] = " DIV Z Y";
	matrix[11][0] = " AND Z Y";
	matrix[11][2] = "#";
	matrix[11][32] = "#";
	matrix[11][22] = "#";
	matrix[11][8] = "#";
	matrix[11][13] = "#";
	matrix[11][30] = "#";
	matrix[11][31] = "#";
	matrix[11][3] = "#";
	matrix[11][4] = "#";
	matrix[11][28] = "#";
	matrix[11][33] = "#";
	matrix[11][9] = "#";
	matrix[11][11] = "#";
	matrix[11][23] = "#";
	matrix[11][12] = "#";
	matrix[12][20] = " NUM";
	matrix[12][18] = " ID";
	matrix[12][27] = " PARE S PARD";
	matrix[12][35] = " TRUE";
	matrix[12][15] = " FALSE";
	matrix[12][21] = " NOT Z";



	list* stack = new_list();
	list* final = new_list();
	list_push_front(stack,"A",0);
	buffer* word = new_buffer();
	node* no = tokens->head;

	while(no != NULL){  // fazendo uma copia da lista de tokens da entrada
		list_push_back(final,no->data,no->row);
		no = no->next;
	}

	char* strstack;
	char* strtokens;
	char* strprod;
	int lenght,row,col;
	

	while(stack->size != 0 && tokens->size != 0){ // repita enquanto a lista de entrada e a pilha nao estiver vazia
		strstack = list_top(stack);  // recebe a string no final da pilha
		strtokens = list_front(tokens); // recebe a string do inicio da lista de entrada
		printf("\nPILHA\n");
		list_print(stack);
		printf("\nENTRADA\n");
		list_print(tokens);
		if( strlen(strstack) > 1){ // se o comprimento da string da pilha > 1, logo a string é um terminal
			if(strcmp(strstack,strtokens) == 0){ // compara as strings das duas listas, caso for igual desempilha
				list_pop_back(stack);
				list_pop_front(tokens);
			}
			else{
				printf("Erro <%s,%d>\n",tokens->head->data,tokens->head->row);
				printf("\n ERRO TOPO DA PILHA E INCIO DA ENTRADA SAO DIFERENTES\n");
				return NULL;
			}
		}
		else{ // caso em que topo da pilha é variavel 		
			row=hashing(strstack,26);
			col=indice(strtokens);
			if(row == 4 && col == 11){ // tratamento para caso caia no else que tem duas produçoes
				if(strcmp(strtokens,"ELSE") == 0){
					list_pop_back(stack);
					list_push_back(stack,"P",tokens->head->row);
					list_push_back(stack,"ELSE",tokens->head->row);		
				}
				else{
					list_pop_back(stack);
				}
				printf("\nENTROU NO ELSE\n");
			}
			else{ // caso em que se busca a produçao na matrix
				strprod = matrix[row][col];
				
				printf("\nMATRIZ(linha %d coluna %d) - PRODUCAO ENCONTRADA NA TABELA SINTATICA (%s )\n",row,col,strprod);
				if(strcmp(strprod,"@") == 0 ){ // caso em que a produçao na matriz nao existe, situaçao de rejeiçao da entrada
					printf("Erro <%s,%d>\n",tokens->head->data,tokens->head->row);
					printf("\nERRO, NAO EXISTE UMA PRODUÇAO DE TROCA PARA ESSA VARIAVEL\n");
					return NULL;
				}
				else if(strcmp(strprod,"#") == 0){ // caso em que a produçao encontrada na matriz vai para o vazio
					list_pop_back(stack); // removemos o topo da pilha
				}
				else{ // situaçao em que pegamos a produçao da matrix e empilhamos ao contrario no lugar do topo da pilha
					lenght = strlen(strprod); // pegamos o tamanho da string produçao para destrinchar as sub palavaras
					list_pop_back(stack); // removemos o topo da pilha para empilhar as novas produçoes
					while(lenght > 0){ // separando as strings da produçao na matrix
						if(isspace (strprod[lenght - 1]) == 0){ // caractere linho na string strprod é um caractere nao nulo
							buffer_push_front(word,strprod[lenght - 1]); // insiro em um buffer temporario
						}
						else{ // caso encontre um espaço em branco na string da produçao, definimos o que lemos como uma palavra completa
							buffer_push_back(word,'\0'); // colocamos um fim de string para encerrar a palavra
							list_push_back(stack,word->data,tokens->head->row);	// inserimos a nova produçao no topo da pilha
							clear_buffer(word); // limpa o buffer temporario para armazenar uma nova produçao
						}
						lenght --; // auto decremento para percorrer a produçao inteira
					}
				}
			}  
		}
	}
	if(stack->size == 0 && tokens->size == 0){
		free_buffer(word);
		free_list(stack);
		free_list(tokens);
		printf("\nRETORNOU LISTA FINAL PARA ANALISE SEMANTICA\n");
		return final; // entrada aceita, tem que dar free nas listas
	}
	else if(stack->size != 0){
		printf("Erro <%s,%d>\n",stack->head->data,stack->head->row);
		free_buffer(word);
		free_list(stack);
		free_list(tokens);
		free_list(final);
		printf("\nPILHA FICOU VAZIA\n");
		return NULL;
	}
	else{
		printf("Erro <%s,%d>\n",tokens->head->data,tokens->head->row);
		free_buffer(word);
		free_list(stack);
		free_list(tokens);
		free_list(final);
		printf("\nENTRADA FICOU VAZIA\n");
		return NULL;
	}
}
