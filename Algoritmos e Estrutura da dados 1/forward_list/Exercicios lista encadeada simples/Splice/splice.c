void splice(list* a, list* b, int pos);

void splice(list* a, list* b, int pos){
	node* n=NULL;
	node* m=NULL;
	if(a->head!=NULL && b->head!=NULL){
		m=list_at(a,pos-1);
		n=list_at(a,pos);
		m->next=b->head;
		m=NULL;
		m=list_at(b,b->size-1);
		m->next=n;
		a->size+=b->size;
		}
	else if(a->head==NULL && b->head!=NULL){
		a->head=b->head;
		a->size=b->size;
	}
	b->head=NULL;
	free(b);
}
