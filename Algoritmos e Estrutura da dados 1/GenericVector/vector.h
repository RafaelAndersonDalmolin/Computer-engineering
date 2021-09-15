#ifndef _VECTOR_H_
#define _VECTOR_H_
	/*
	Tipo 				 	Formato		valor
	char 				 	%c 			1
	unsigned char 			%c 			2
	int 				 	%d 			3
	unsigned int		 	%u 			4
	long int 			 	%li 		5
	unsigned long int	 	%lu 		6
	short int			 	%hi 		7
	unsigned short int	 	%hu 		8
	float				 	%f 			9
	double				 	%lf 		10
	long double 		 	%lf			11

	Definir o valor para o tipo de dado a ser armazenado em vector
	Example: 
		#define typedata valor  
	*/
/****************/
#define	typedata	1 
/****************/
#if typedata == 1
	typedef char type;
	#define print() printf("%c|",(*v).data[i]);
#elif typedata == 2
	typedef unsigned char type;
	#define print() printf("%c|",(*v).data[i]);
#elif typedata == 3
	typedef int type;
	#define print() printf("%d|",(*v).data[i]);
#elif typedata == 4
	typedef unsigned int type;
	#define print() printf("%u|",(*v).data[i]);	
#elif typedata == 5
	typedef long int type;
	#define print() printf("%li|",(*v).data[i]);
#elif typedata == 6
	typedef unsigned long int type;
	#define print() printf("%lu|",(*v).data[i]);
#elif typedata == 7
	typedef short int type;
	#define print() printf("%hi|",(*v).data[i]);
#elif typedata == 8
	typedef unsigned short int type;
	#define print() printf("%hu|",(*v).data[i]);
#elif typedata == 9
	typedef float type;
	#define print() printf("%.f|",(*v).data[i]);
#elif typedata == 10
	typedef double type;
	#define print() printf("%lf|",(*v).data[i]);
#elif typedata == 11
	typedef long double type;
	#define print() printf("%lf|",(*v).data[i]);
#else
	#error tipo de dados de typedata nao foi definido
#endif
typedef struct{
    type *data;     // ponteiro para o tipo definido em type
    int size;		// tamanho atual do vetor
    int capacity;  	// tamanho reservado em memória 
} vector;
vector *vector_new(void); // aloca memoria inicial para vector 
void vector_free(vector *v); // libera memoria do vector
void vector_resize(vector *v); // realoca mais memoria para vector

void vector_insert(vector *v,type value,int index); //insere um elemento no indice i
void vector_push_front(vector *v,type value); // insere um elemento no inicio
void vector_push_back(vector *v,type value); // insere um elemento no fim

type vector_erase(vector *v,int index); //remove e retorna o elemento na posicao passada
type vector_pop_front(vector *v); //remove e retorna o elemento do incio
type vector_pop_back(vector *v); //remove e retorna o elemento do fim

type *vector_at(vector* v,int index);// Retorna um ponteiro para item em index 
type vector_get(vector* v,int index); // Retorna o valor na posicao index    
void vector_set(vector* v,int index,type value);// Altera o valor na posição index

void vector_print(vector *v); // imprime os elementos de vector
#endif