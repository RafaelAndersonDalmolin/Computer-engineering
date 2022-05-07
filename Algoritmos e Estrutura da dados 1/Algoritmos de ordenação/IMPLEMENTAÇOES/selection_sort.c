void selectionsort(int* v, int size) { 
	int min;
	for (int i = 0; i < (size-1); i++){	
		min = i;
		for (int j = (i+1); j < size; j++) {
			if(v[j] < v[min]){ 
	     		min = j;
			}
			compare();
		}
	if (v[i] != v[min]){
		swap(v,i,min);
	 	exchange();
	}
  }
}
