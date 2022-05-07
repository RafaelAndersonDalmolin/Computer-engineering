void decr_random(int* v, int size)  // gerar vetor aleatorio decrescente
{  
	v[size-1]=rand()%100;
	for(int i = size-2; i >= 0; i--)
	{
		v[i]=(v[i+1])+(rand()%MAX_VALUE);	
	}
}
