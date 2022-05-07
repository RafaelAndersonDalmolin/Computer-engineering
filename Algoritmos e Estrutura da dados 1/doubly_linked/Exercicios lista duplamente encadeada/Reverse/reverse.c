void reverse(list* a);
void reverse(list* a){
	if(a->size!=0 && a->size!=1)	
		node* n=a->tail;
		for(int i=a->size-1; i>0; i--)
		{
			list_push_back(a,n->value);
			list_erase(a,i);
			n=n->prev;
		}
		list_push_back(a,n->value);
		list_erase(a,0);
}
