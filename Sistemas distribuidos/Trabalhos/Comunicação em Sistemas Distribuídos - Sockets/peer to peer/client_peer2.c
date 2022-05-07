#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_MSG 1024
#define PORTA 4321

int main(int argc , char *argv[]){
	// variaveis
	int socket_desc;
	struct sockaddr_in servidor;
	char mensagem[MAX_MSG];
	int tamanho;
	char *ipservidor = "127.0.0.1";


    //Passo 1: Criar o socket 
	// AF_INET = ARPA INTERNET PROTOCOLS
	// SOCK_STREAM = TCP
	// 0 = protocolo IP
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
     
	if (socket_desc == -1){
		printf("Nao foi possivel criar socket\n");
		return -1;	
	}

	/* Informacoes para conectar no servidor */
	// IP do servidor
	// familia ARPANET
	// Porta - hton = host to network short (2bytes)
	servidor.sin_addr.s_addr = inet_addr(ipservidor);
	servidor.sin_family = AF_INET;
	servidor.sin_port = htons(PORTA);

	//Conectar no servidor
	if (connect(socket_desc , (struct sockaddr *)&servidor , sizeof(servidor)) < 0){
		printf("Nao foi possivel conectar\n");
		return -1;
	}
	printf("Conectado no servidor!!!\n");
	printf("Pronto para troca de mensagens\n");
	/*****************************************/
	/*******COMUNICAO - TROCA DE MENSAGENS **************/
	//Passo 3: Realizar a comunição com o servidor segundo um protocolo.
	// Inicia troca de mensagens
	do{
		//captura escrita no terminal
		fgets(mensagem,MAX_MSG,stdin);
		mensagem[strlen(mensagem)-1] = '\0';
		// Enviando mensagem para o servidor
		if( write(socket_desc , mensagem , strlen(mensagem)) < 0){
			printf("Erro ao enviar mensagem\n");
		return -1;
		}
		if(strcmp(mensagem,"close_connection") == 0){
			//Passo 4: Encerrar conexão
			close(socket_desc);
			printf("Cliente finalizado com sucesso!\n");
			return 0;
		}
		// lendo mensagem enviada pelo servidor
		if((tamanho = read(socket_desc,mensagem, MAX_MSG)) < 0){
			perror("Erro ao receber dados do servidor: ");
			return -1;
		}
		// Coloca terminador de string
		// imprime mensagem recebida
		mensagem[tamanho] = '\0';
		printf("Resposta: ");
		puts(mensagem);
		if(strcmp(mensagem,"close_connection") == 0){
			//Passo 4: Encerrar conexão
			close(socket_desc);
			printf("O servidor finalizou!\n");
			return 0;
		}
	}while(true);
}
