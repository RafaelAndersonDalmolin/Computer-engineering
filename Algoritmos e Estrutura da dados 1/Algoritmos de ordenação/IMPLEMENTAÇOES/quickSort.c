int partition(int* A, int p, int r){
    int x = A[r];
    int i = p;
    int j = r; 
    while (i < j) {
        while (A[i] <= x && i < r)
            i++;
        while (A[j] > x)
            j--;
            
        if (i < j){ 
            swap(A, i, j);
			exchange();
			compare();
		}
    }
	exchange();
    A[p] = A[j];
    A[r] = x;
    return r;
}
void quicksort(int* v, int inicio, int fim)
{
	if(inicio < fim)
	{
		int p = partition(v, inicio, fim);
		quicksort(v, inicio, p-1);
		quicksort(v, p+1, fim);
	}
}
