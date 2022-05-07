void cres_random(int* v, int size)  // gerar vetor aleatorio crescente
{  
	v[0]=rand()%MAX_VALUE;
	for(int i = 1; i < size; i++)
	{
		v[i]=((v[i-1])+(rand()%MAX_VALUE));	
	}
}
