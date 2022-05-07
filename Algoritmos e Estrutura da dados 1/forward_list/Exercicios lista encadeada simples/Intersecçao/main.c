#include"forward_list.h"
int main(){
    list* a=NULL; list* b=NULL; list* c=NULL; int y=0;  a=new_list(); b=new_list();
	scanf("%d",&y);     //A primeira linha indica o número de operações que serão descritas nas linhas a seguir
    for(int i=y; i>0; i--)   //inicia o for para receber o numero de operaçoes indicado anteriormente
   	{	
		int value=0;
		scanf("%d",&value);
		set_insert(a,value);

	}
	y=0;
	scanf("%d",&y);     //A primeira linha indica o número de operações que serão descritas nas linhas a seguir
    for(int i=y; i>0; i--)   //inicia o for para receber o numero de operaçoes indicado anteriormente
   	{	
		int value=0;
		scanf("%d",&value);
		set_insert(b,value);

	}
	c=set_intersection(a,b);
	list_print(c);

}
