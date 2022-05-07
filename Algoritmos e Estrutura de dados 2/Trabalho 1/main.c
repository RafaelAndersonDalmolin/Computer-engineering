#include"grafo.h"
int main(){
	grafo* g=new_grafo(); int i=0,v,e;
	do{
	printf("1. Inserir Vértices\n");
	printf("2. Inserir Arestas\n");
	printf("3. Visualizar Grafo\n");
	printf("4. Remover Vértices\n");
	printf("5. Remover Arestas\n");
	printf("6. Sair\n");
	scanf("%d",&i);
		if(i==1){
			printf("Digite o valor do vértice a ser inserido!\n");
			scanf("%d",&v);
			insert_vertex(g,v);
			sleep(5);
			system("clear");
		}
		else if(i==2){
			printf("Digite quais vértices serão ligados!\n");
			scanf("%d",&v);
			scanf("%d",&e);
			insert_edge(g,v,e);
			sleep(5);
			system("clear");
		}
		else if(i==3){
			system("clear");
			print_grafo(g);
		}
		else if(i==4){
			printf("Digite o vértice a ser removido!\n");
			scanf("%d",&v);			
			remove_vertex(g,v);
			sleep(5);
			system("clear");
		}
		else if(i==5){
			printf("Digite em quais vértices será removido a aresta!\n");
			scanf("%d",&v);				
			scanf("%d",&e);
			remove_edge(g,v,e);
			sleep(5);
			system("clear");
		}
		else if(i==6){
			free_grafo(g);
		}
		else{
			printf("Digite um numero correspondente a uma das opcoes!\n");
			sleep(5);
			system("clear");
		}
	}while(i!=6);
}
