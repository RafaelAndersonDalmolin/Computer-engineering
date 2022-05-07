void set_diff(list* a, list* b);
void set_diff(list* a, list* b){
	node* lista=a->head;
	node* listb=b->head;
	int i=0,y=0;
	while(lista!=NULL){
		while(listb!=NULL){
			if(lista->value==listb->value){
				i=1;
			}
			listb=listb->next;
		}
		if(i==1){		
			list_erase(a,y);
			i=0;
			y--;
		}
	y++;
	listb=b->head;	
	lista=lista->next;
	}
	free(b);
}
