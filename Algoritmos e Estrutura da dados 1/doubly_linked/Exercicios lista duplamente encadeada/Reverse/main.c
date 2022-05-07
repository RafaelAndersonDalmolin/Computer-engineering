#include"doubly_linked.h"
int main(){
	list* apt=NULL;  int y=0;
	apt=new_list();
	scanf("%d",&y);     //A primeira linha indica o número de operações que serão descritas nas linhas a seguir
    for(int i=y; i>0; i--)   //inicia o for para receber o numero de operaçoes indicado anteriormente
   	{	
		int value=0;
		scanf("%d",&value);
		list_push_back(apt,value);

	}
	list_print(apt);
	reverse(apt);
	list_print(apt);
	




}
