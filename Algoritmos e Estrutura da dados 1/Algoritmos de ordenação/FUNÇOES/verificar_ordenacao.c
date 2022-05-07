void ordenado(int*v ,int size){   // verificar se o vetor esta ordenado
	for(int i = 0; i < size-1; i++)
	{
		if(v[i]>v[i+1]){
			printf("O VETOR ESTA DESORDENADO!\n");
			return;
		}
	}
	printf("O VETOR ESTA ORDENADO!\n");
}
