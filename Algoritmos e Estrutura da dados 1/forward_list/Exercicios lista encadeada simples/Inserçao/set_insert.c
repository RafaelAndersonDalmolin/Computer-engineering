void set_insert(list* l,int value);

void set_insert(list* l,int value){	
	node* n=l->head;
	int i=0;
	while(n!=NULL){
		if(n->value==value)
		{
			i=1;
		}		
		n=n->next;
	}
	if(i!=1){
		list_push_back(l,value);
		}	
	}
}

