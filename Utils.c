#include <limits.h>

//Get max element of array
int max_element(int* A, int N){
	int max = INT_MIN;
	for (int i = 0; i < N; ++i)
		if (A[i] > max)
			max = A[i];
	return max;
}

//Get min element of array
int min_element (int* A, int N){
	int min = INT_MAX;
	for (int i = 0; i < N; ++i)
		if (A[i] < min)
			min = A[i];
	return min;
}