void bubblesort(int* v, int size){
	
	for(int i=size-1; i>0; i--){
		for(int i=0; i<size-1; i++){			
			compare();
			if(v[i]>v[i+1]){
				swap(v,i,i+1);
				exchange();	
			}
		}
	}
}
