#include"grafo.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool exist_vertex(grafo* g,int v){		//verifica se um vertice existe
	node* n=g->head;
	while(n!=NULL){
		if(n->vertex==v){
			return true;
		}
		n=n->bellow;
	}
	return false;	
}
bool exist_edge(node* v,int e){   // verifica se uma aresta existe
	edge* n=v->head;
	while(n!=NULL){
		if(n->vertex==e){
			return true;
		}
		n=n->next;
	}
	return false;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void new_vertex(grafo* g,int value){  // cria uma nova estrutura do tipo node
	node*n =(node*)malloc(sizeof(node));	
	if(g->size==0){		//1º caso o grafo nao ter nenhum vertice
		n->vertex=value;
		n->size=0;
		n->head=NULL;
		n->tail=NULL;
		n->up=NULL;
		n->bellow=NULL;
		g->head=n;
		g->tail=n;
	}
	else{				//2º caso o grafo ja tenha vertices
		n->vertex=value;
		n->size=0;
		n->head=NULL;
		n->tail=NULL;
		n->up=g->tail;
		g->tail->bellow=n;
		n->bellow=NULL;
		g->tail=n;	
	}
	g->size++;
}
void insert_vertex(grafo* g,int value){ // inserir um vertice, sempre inserindo o vertice no final da lista
	bool a=exist_vertex(g,value); //verificar se o vertice ja existe no grafo	
	if(a==false){
		new_vertex(g,value);
	}
	else{
		printf("IMPOSSIVEL INSERIR O VERTICE, O MESMO JA EXISTE!\n");
	}
}
void new_edge(node* n,int v){     // cria uma nova estrutura do tipo edge 
	edge* e=(edge*)malloc(sizeof(edge));
	if(n->size==0){	
		e->vertex=v;
		e->prev=NULL;
		e->next=NULL;
		n->head=e;
		n->tail=e;
	}
	else{
		e->vertex=v;
		e->prev=n->tail;
		e->next=NULL;
		n->tail->next=e;
		n->tail=e;
	}
	n->size++;
}
void insert_edge(grafo* g,int v, int e){	// inserir uma aresta, sempre inserindo a aresta no final da lista
	if(v!=e){	// verifica se a aresta que vai ser inserida sera um laço
		bool a=exist_vertex(g,v);
		bool b=exist_vertex(g,e);
		if(a==true && b==true){ 	//verifica se os vertices existem
			node* v1=search_vertex(g,v);
			node* v2=search_vertex(g,e);
			bool c=exist_edge(v1,e);	// verifica se ja existe uma aresta entre os vertices
			if(c==false){
				new_edge(v1,e);
				new_edge(v2,v);			
			}
			else{
				printf("IMPOSSIVEL INSERIR A ARESTA, POIS A MESMA JA EXISTE!\n");
			}
		}
		else{
			if(a==false && b==false){
				printf("IMPOSSIVEL INSERIR A ARESTA,POIS OS VERTICES NAO EXISTEM!\n");
			}
			else if(a==true && b==false){
				printf("IMPOSSIVEL INSERIR A ARESTA,POIS O VERTICE %d NAO EXISTE!\n",e);
			}
			else{
				printf("IMPOSSIVEL INSERIR A ARESTA,POIS O VERTICE %d NAO EXISTE!\n",v);
			}
		}
	}
	else{
		printf("IMPOSSIVEL FAZER UMA ARESTA LAÇO!\n");
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
node* search_vertex(grafo* g,int v){    //caso um vertice exista entao procuramos pelo seu endereço
	node* n=g->head;
	while(n->vertex!=v){
		n=n->bellow;
	}
	return n;
}
edge* search_edge(node* n,int a){	//caso uma aresta exista entao procuramos pelo seu endereço
	edge* e=n->head;
	while(e->vertex!=a){
		e=e->next;
	}
	return e;
} 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void r_edge(node* n,edge* e){ // apaga a estrutura edge
	if(e->prev==NULL && e->next==NULL){  //UNICA ARESTA,ELA É O INICIO E FIM DA LISTA
		n->head=NULL;
		n->tail=NULL;
		n->size--;
		free(e);
	}
	if(e->prev==NULL && e->next!=NULL){  //ARESTA NO INICIO DA LISTA  
		n->head=e->next;
		e->next->prev=NULL;
		n->size--;
		free(e);
	}
	if(e->next==NULL && e->prev!=NULL){  //ARESTA NO FIM DA LISTA
		n->tail=e->prev;
		e->prev->next=NULL;
		n->size--;
		free(e);
	}
	if(e->prev!=NULL && e->next!=NULL){   // ARESTA NO MEIO DA LISTA
		e->prev->next=e->next;
		e->next->prev=e->prev;
		n->size--;
		free(e);
	}
}
void remove_edge(grafo*g,int v1,int v2){  // Remove aresta
	if(v1!=v2){	//verifica se a aresta a ser removida é do tipo laço
		bool a=exist_vertex(g,v1);  
		bool b=exist_vertex(g,v2);	
		if(a==true && b==true){ // verifica se os vertices que nao serao mais incidentes existem
			node* n1=search_vertex(g,v1); //busca pelo vertice
			bool c=exist_edge(n1,v2); // verifica se os vertices sao incidentes
			if(c==true){  // aresta entre os vertices existem, entao remove-se as arestas nos dois vertices
				edge* e1=search_edge(n1,v2);
				r_edge(n1,e1);
				node* n2=search_vertex(g,v2);
				edge* e2=search_edge(n2,v1);
				r_edge(n2,e2);	
			}
			else{
				printf("IMPOSSIVEL REMOVER ARESTA, ELA NAO EXISTE!\n");
			}
		}
		else{
			if(a==false && b==false){
				printf("IMPOSSIVEL REMOVER ARESTA ENTRE OS VERTICES, POIS OS VERTICES NAO EXISTEM!\n");
			}
			else if(a==true && b==false){
				printf("IMPOSSIVEL REMOVER A ARESTA ENTRE OS VERTICES, POIS O VERTICE %d NAO EXISTE!\n",v2);
			}
			else{
				printf("IMPOSSIVEL REMOVER A ARESTA ENTRE OS VERTICES, POIS O VERTICE %d NAO EXISTE!\n",v1);
			}
		}
	}
	else{
		printf("IMPOSSIVEL REMOVER ARESTA, ELA NAO EXISTE!\n");
	}
}
void r_vertex(grafo* g,node* n){  // apaga a estrutura node
	if(n->up==NULL && n->bellow==NULL){  //UNICA ARESTA, INICIO E FIM DA LISTA
		g->head=NULL;
		g->tail=NULL;
		g->size--;
		free(n);
	}
	if(n->up==NULL && n->bellow!=NULL){  //ARESTA NO INICIO DA LISTA  
		g->head=n->bellow;
		n->bellow->up=NULL;
		g->size--;
		free(n);
	}
	if(n->bellow==NULL && n->up!=NULL){  //ARESTA NO FIM DA LISTA
		g->tail=n->up;
		n->up->bellow=NULL;
		g->size--;
		free(n);
	}
	if(n->up!=NULL && n->bellow!=NULL){   // ARESTA NO MEIO DA LISTA
		n->up->bellow=n->bellow;
		n->bellow->up=n->up;
		g->size--;
		free(n);
	}
}
void remove_vertex(grafo *g,int v){ //remove o vertice
	bool a=exist_vertex(g,v);		
	if(a==true){		//verifica se o vertice a ser removido existe
		node* n=search_vertex(g,v); //procura pelo vertice
		edge* e=n->head;			// verifica se o vertice tem arestas e remove todas antes de apagar o vertice
		int x;
		while(e!=NULL){
			x=e->vertex;
			e=e->next;
			remove_edge(g,x,v);		//funçao que remove arestas
		}
		r_vertex(g,n);				//apos remover todas as arestas, chama a funçao que remove o vertice
	}
	else{
		printf("IMPOSSIVEL REMOVER POIS O VERTICE NAO EXISTE!\n");
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void print_grafo(grafo* g){ // IMPRIMIR O GRAFO COMPLETO	
	node* n=g->head;
	edge* e=NULL;
	if(n!=NULL){
		e=n->head;
	}
	printf("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
	if(g->size==0){	
		printf("GRAFO NULO\n");
	}
	while(n!=NULL){
		printf("[%d]",n->vertex);
		while(e!=NULL){
			printf("->");
			printf("(%d)",e->vertex);
			e=e->next;
		}
		printf("\n");
		n=n->bellow;
		if(n!=NULL){
			e=n->head;
		}
		
	}
	printf("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
grafo* new_grafo(){  //alocar memoria para uma estrutura grafo
	grafo* g = (grafo*) malloc(sizeof(grafo));
	g->size=0;
	g->head=NULL;
	g->tail=NULL;
	return g;
}
void free_grafo(grafo *g){  // desaloca memoria do grafo todo, apagando a estrutura sem deixar memoria alocada!
	if(g->size!=0){
		node* n=g->head;
		int x;
		while(n!=NULL){
			x=n->vertex;
			n=n->bellow;
			remove_vertex(g,x);
		}
		free(g);
	}
}
