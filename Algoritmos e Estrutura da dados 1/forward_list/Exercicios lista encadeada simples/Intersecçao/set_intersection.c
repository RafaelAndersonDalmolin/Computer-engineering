list* set_intersection(list* a, list* b);

list* set_intersection(list*a,list*b){
	node* lista=a->head;
	node* listb=b->head;
	list* c=new_list();
	int i=0;
	while(lista!=NULL){
		while(listb!=NULL){
			if(lista->value==listb->value){
				i=1;
			}
			listb=listb->next;
		}
		if(i==1){		
			list_push_back(c,lista->value);
			i=0;
		}
	listb=b->head;	
	lista=lista->next;
	}
	free(a);
	free(b);
	return c;
}
