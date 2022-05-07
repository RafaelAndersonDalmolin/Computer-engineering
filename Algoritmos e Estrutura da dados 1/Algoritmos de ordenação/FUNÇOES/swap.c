void swap(int* vetor, int a, int b);

void swap(int* vetor, int a, int b){
    int aux = vetor[a];
    vetor[a] =vetor[b];
    vetor[b] = aux;
}
