#include"doubly_linked.h"
int main(){
	list *apt=NULL; int y=0,x=0;
	apt=new_list();
	scanf("%d",&x);		// ignorar entrada
	scanf("%d",&y);     //A primeira linha indica o número de operações que serão descritas nas linhas a seguir
    
    for(int i=y; i>0; i--)   //inicia o for para receber o numero de operaçoes indicado anteriormente
    {
            char a[15]; int valor=0,posi=0;
            scanf("%s",a);                  // Lê a string de entrada

            if( 0== (strcmp(a,"push_back"))) // Compara a string de entrada para receber o valor
            {
                scanf("%d",&valor);
                list_push_back(apt,valor);      // chama a funçao push back para p com o Valor
                list_print(apt);
            }
            if(0==(strcmp(a,"push_front")))
            {
                scanf("%d",&valor);
                list_push_front(apt,valor);    
                list_print(apt);
            }
            if(0==(strcmp(a,"insert")))
            {
                scanf("%d %d",&valor,&posi);
                list_insert(apt,valor,posi);
                list_print(apt);
            }
            if(0==(strcmp(a,"pop_back")))
            {
                list_pop_back(apt);
                list_print(apt);
            }
            if(0==(strcmp(a,"pop_front")))
            {
                list_pop_front(apt);
                list_print(apt);
            }
            if(0==(strcmp(a,"set")))
            {
                scanf("%d %d",&posi,&valor);
                list_set(apt,posi,valor);
                list_print(apt);
            }
            if(0==(strcmp(a,"erase")))
            {
                scanf("%d",&posi);
                list_erase(apt,posi);
                list_print(apt);
            }

    }
}


