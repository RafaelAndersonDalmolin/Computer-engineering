void merge(int* v, int* aux, int inicio, int meio, int fim){
	int i = inicio;
	int j = meio+1;
	int k = inicio;
	int t = inicio;

	for(k = inicio; k <= fim; k++)
	{
		if(i > meio)
		{
			aux[k] = v[j++];
		}
		else if(j > fim)
		{
			aux[k] = v[i++];
		}
		else if(menorigual(v[i], v[j]))
		{
			compare();
			aux[k] = v[i++];
		}
		else
		{
			aux[k] = v[j++];
			compare();
			
		}
		exchange();

	}
	for(t = inicio; t <= fim; t++)
	{
		v[t] = aux[t];
	}
	
}
void mergesort(int* v, int* aux, int inicio, int fim)
{
	if(inicio < fim)
	{
		int p = (fim+inicio)/2;
		mergesort(v, aux, inicio, p);
		mergesort(v,aux, p+1, fim);

		merge(v, aux,inicio, p, fim);
	}
}
