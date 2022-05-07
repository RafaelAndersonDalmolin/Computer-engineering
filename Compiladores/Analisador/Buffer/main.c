#include"buffer.h"
void main (void){
	buffer* string;	char* word;
	string=new_buffer();
	buffer_push_back(string,'R');
	buffer_push_back(string,'a');
	buffer_push_back(string,'f');
	buffer_push_back(string,'a');
	buffer_push_back(string,'\0');
	buffer_print(string);
	printf("%s\n",string->data);
	free_buffer(string);
}
