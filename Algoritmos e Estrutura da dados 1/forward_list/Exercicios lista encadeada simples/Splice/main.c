#include"forward_list.h"

// void splice(list* a, list* b, int pos){
// 	node* n=NULL;
// 	node* m=NULL;
// 	if(a->head!=NULL && b->head!=NULL){
// 		m=list_at(a,pos-1);
// 		n=list_at(a,pos);
// 		m->next=b->head;
// 		m=NULL;
// 		m=list_at(b,b->size-1);
// 		m->next=n;
// 		a->size+=b->size;
// 		}
// 	else if(a->head==NULL && b->head!=NULL){
// 		a->head=b->head;
// 		a->size=b->size;
// 	}
// 	b->head=NULL;
// 	free(b);
// }

int main(){
	list* apt=NULL; list* aptB=NULL;  int y=0;
	apt=new_list();
	aptB=new_list();
	scanf("%d",&y);     //A primeira linha indica o número de operações que serão descritas nas linhas a seguir
    for(int i=y; i>0; i--)   //inicia o for para receber o numero de operaçoes indicado anteriormente
   	{	
		int value=0;
		scanf("%d",&value);
		list_push_back(apt,value);

	}
	scanf("%d",&y);     //A primeira linha indica o número de operações que serão descritas nas linhas a seguir
    for(int i=y; i>0; i--)   //inicia o for para receber o numero de operaçoes indicado anteriormente
   	{	
		int value=0;
		scanf("%d",&value);
		list_push_back(aptB,value);

	}
	scanf("%d",&y);
	splice(apt,aptB,y);
	list_print(apt);




}
