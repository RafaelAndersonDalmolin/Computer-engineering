#include"vector.h"
#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<string.h>
vector *vector_new(void){
	vector *v = malloc(sizeof(vector));
	(*v).data = malloc(sizeof(type)*2);  //(*v).data == v->data
	(*v).size=0;
	(*v).capacity=2;
	return v;
}
void vector_free(vector *v){
	free((*v).data);
	free(v); 
}
void vector_resize(vector *v){
	(*v).capacity *=2;
	(*v).data = realloc((*v).data,(*v).capacity*sizeof(type));
}
void vector_insert(vector *v,type value,int index){
	assert(index >= 0 && index <= (*v).size);
	if((*v).capacity == (*v).size){
		vector_resize(v);
	}
	for(int i = (*v).size; index < i ; i--){
		(*v).data[i] = (*v).data[i-1];
	}
	(*v).data[index] = value;
	(*v).size++;
}
void vector_push_front(vector *v,type value){
	vector_insert(v,value,0);
}
void vector_push_back(vector *v,type value){
	vector_insert(v,value,(*v).size);
}
type vector_erase(vector *v,int index){
	assert(index >= 0 && index < (*v).size);
	type value=(*v).data[index];
	(*v).size--;
	for(; index < (*v).size; index++){
		(*v).data[index]=(*v).data[index+1];
	}
	return value;
}
type vector_pop_front(vector *v){
	return vector_erase(v,0);
}
type vector_pop_back(vector *v){
	return vector_erase(v,(*v).size-1);
}
type *vector_at(vector* v,int index){
	assert(index >= 0 && index < (*v).size);
	return &((*v).data[index]);
}
type vector_get(vector* v,int index){
	assert(index >= 0 && index < (*v).size);
	return (*v).data[index];
}
void vector_set(vector* v,int index,type value){
	assert(index >= 0 && index < (*v).size);
	(*v).data[index]=value;
}
void vector_print(vector *v){
	printf("[Size/Capacity]\n");
	printf("[%d/%d]\t",(*v).size,(*v).capacity);
	if((*v).size > 0){
		printf("|");
	}
	for(int i=0; i<(*v).size; i++){
		print()
	}
	printf("\n");
}