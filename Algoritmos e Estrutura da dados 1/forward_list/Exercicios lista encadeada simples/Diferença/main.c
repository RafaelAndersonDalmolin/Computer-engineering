#include"forward_list.h"
int main(){
    list* a=NULL; list* b=NULL; int y=0;  a=new_list(); b=new_list();
	scanf("%d",&y);     //A primeira linha indica o número de operações que serão descritas nas linhas a seguir
    for(int i=y; i>0; i--)   //inicia o for para receber o numero de operaçoes indicado anteriormente
   	{	
		int value=0;
		scanf("%d",&value);
		set_insert(a,value);

	}
	list_print(a);
	y=0;
	scanf("%d",&y);     //A primeira linha indica o número de operações que serão descritas nas linhas a seguir
    for(int i=y; i>0; i--)   //inicia o for para receber o numero de operaçoes indicado anteriormente
   	{	
		int value=0;
		scanf("%d",&value);
		set_insert(b,value);

	}
	list_print(b);
	set_diff(a,b);
	list_print(a);

}
