void insertionsort(int* v, int size) {
	int atual,j;

	for (int i = 1; i < size; i++) {
		atual = v[i];
		exchange();
		for (j = i - 1; (j >= 0) && (atual < v[j]); j--) {
			v[j + 1] = v[j];
			exchange();
        }
		compare();
		exchange();
		v[j+1] = atual;		
	}
}
