#include"doubly_linked.h"
int main(){
	list *apt=new_list();
	list_push_back(apt,"ID",1);
	list_push_back(apt,"VAR",1);
	list_push_back(apt,"INTEIRO",2);
	list_push_back(apt,"ATRIB",3);
	list_push_back(apt,"ADD",4);
	list_print(apt);
	list_pop_back(apt);
	list_print(apt);
	list_pop_back(apt);
	list_print(apt);
	list_pop_back(apt);
	list_print(apt);
	list_pop_back(apt);
	list_print(apt);
	list_pop_back(apt);
	list_print(apt);
	free_list(apt);
}


