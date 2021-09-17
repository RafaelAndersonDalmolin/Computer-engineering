#include "vector.h"
#include <stdio.h>
void main () {
	vector *vetor = vector_new();
	vector_push_back(vetor,'R');
	vector_push_back(vetor,'A');
	vector_push_back(vetor,'F');
	vector_push_back(vetor,'A');
	vector_push_back(vetor,'E');
	vector_push_back(vetor,'L');
	vector_print(vetor);
	vector_free(vetor);
}