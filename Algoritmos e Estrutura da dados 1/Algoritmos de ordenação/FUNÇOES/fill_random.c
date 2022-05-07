void fill_random(int* v, int size)  // gerar vetor aleatorio
{
	for(int i = 0; i < size; i++)
	{
		v[i] =rand()%MAX_VALUE;
	}
}
