list* set_union(list* a, list* b);
list* set_union(list* a, list* b){
	node* lista=a->head;
	node* listb=b->head;
	list* c=new_list();
	int i=0;
	while(lista!=NULL){		
		list_push_back(c,lista->value);
		lista=lista->next;
	}
	lista=a->head;
	while(listb!=NULL){
		while(lista!=NULL){
			if(lista->value==listb->value){
				i=1;
			}
			lista=lista->next;
		}
		if(i==0){		
			list_push_back(c,listb->value);
			i=0;
		}
	i=0;
	lista=a->head;	
	listb=listb->next;
	}
	free(a);
	free(b);
	return c;

}
