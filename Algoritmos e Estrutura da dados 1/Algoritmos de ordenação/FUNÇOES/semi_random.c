void semi_random(int* v, int size)  // gerar vetor aleatorio crescente
{  
	v[0]=rand()%100;
	for(int i = 1; i < size; i++){
		v[i]=(v[i-1])+(rand()%MAX_VALUE);	
	}
	int x=(size*0.15);
	printf("%d\n",x);
	for(int i=0; i<x; i++){
		swap(v,(rand()%size),(rand()%size));
	}
}
