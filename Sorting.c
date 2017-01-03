#include "Sorting.h"
#include "Utils.h"
#include <stdlib.h>
#include <string.h>
#define SWAP(X, Y)	((X)^=(Y), (X)^=(Y), (X)^=(Y))

/****************************************************
 * Uses bubble sort to sort A[0..N-1]
 ****************************************************/

void BubbleSort(int *A, const unsigned N) {
	if (N < 2) return;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N - 1; j++)
			if (A[j + 1] < A[j])
				SWAP(A[j],A[j+1]);
} //end-BubbleSort

/****************************************************
 * Uses selection sort to sort A[0..N-1]
 ****************************************************/

void SelectionSort(int *A, const unsigned N) {
	if (N < 2) return;

	for (int i = 0; i < N; i++) {
		int i_min = i;
		for (int j = i + 1; j < N; ++j)
			if (A[j] < A[i_min])
				i_min = j;
		if (i_min != i)
			SWAP(A[i], A[i_min]);
	}
} //end-SelectionSort

/****************************************************
 * Uses insertion sort to sort A[0..N-1]
 ****************************************************/

void InsertionSort(int *A, const unsigned N) {
	if (N < 2) return;

	for (int i = 1; i < N; i++)
		for (int j = i; j > 0; j--)
			if (A[j] < A[j - 1])
				SWAP(A[j], A[j - 1]);
} //end-InsertionSort

/****************************************************
 * Uses mergesort to sort A[0..N-1]
 ****************************************************/

void MergeSort(int *A, const unsigned N) {
	//Base case
	if (N < 2) return;

	//Find mid point
	int i_mid = N >> 1;
	//Create left sub array
	int *L = calloc(i_mid, sizeof(int));
	memcpy(L, A, i_mid * sizeof(int));
	//Create right sub array
	int *R = calloc(N - i_mid, sizeof(int));
	memcpy(R, A + i_mid, (N - i_mid) * sizeof(int));

	//Recursion
	MergeSort(L, i_mid);
	MergeSort(R, N - i_mid);

	//Merge
	int i = 0, j = 0, k = 0;
	while (i < i_mid && j < (N - i_mid))
		if (L[i] < R[j])
			A[k++] = L[i++];
		else
			A[k++] = R[j++];
	while (i < i_mid)
		A[k++] = L[i++];
	while (j < (N - i_mid))
		A[k++] = R[j++];

	//Free memory
	free(L);
	free(R);

} //end-MergeSort

/****************************************************
 * Uses quicksort sort to sort A[0..N-1]
 ****************************************************/

void QuickSort(int *A, const unsigned N) {
	//Base case
	if (N < 2)
		return;

	//Partition
	int pivot = *A, left = 0, right = N;
	while (left < right) {
		while (left < right && A[--right] > pivot);
		A[left] = A[right];
		while (left < right && A[++left] < pivot);
		A[right] = A[left];
	}
	A[left] = pivot;
	int mid = left;

	//Recursion
		QuickSort(A, mid);
		QuickSort(A + mid + 1, N - mid - 1);
	
} //end-QuickSort

/****************************************************
 * Uses heapsort to sort A[0..N]
 ****************************************************/

void HeapSort(int *A, const unsigned N) {
	if (N == 0)
		return;

	int temp, n = N, parent = N / 2;

	while (1) {
		if (parent > 0)
			temp = A[--parent];  /* save old value to t */

		else {
			if (--n == 0)
				return;
			temp = A[n];
			A[n] = A[0];
		}

		int index = parent, child = (index << 1) + 1;
		while (child < n) {
			if (child + 1 < n && A[child + 1] > A[child])
				child++;
			if (A[child] > temp) {
				A[index] = A[child];
				index = child;
				child = (index << 1) + 1;
			} else
				break;
		}
		A[index] = temp;
	}
} //end-HeapSort

/****************************************************
 * Uses radixsort to sort A[0..N]
 ****************************************************/

void RadixSort(int *A, const unsigned N) {

	int i;
	int *t_array = (int*)calloc(N, sizeof(int));
	int significantDigit = 1;
	int largestNum = max_element(A, N);

	while (largestNum / significantDigit > 0) {

		int bucket[10] = {0};
		for (i = 0; i < N; i++)
			bucket[(A[i] / significantDigit) % 10]++;
		for (i = 1; i < 10; i++)
			bucket[i] += bucket[i - 1];
		for (i = N - 1; i >= 0; i--)
			t_array[--bucket[(A[i] / significantDigit) % 10]] = A[i];
		for (i = 0; i < N; i++)
			A[i] = t_array[i];
		significantDigit *= 10;
	}
} //end-RadixSort

/****************************************************
 * Uses countingsort to sort A[0..N]
 ****************************************************/

void CountingSort(int *A, const unsigned N) {

	int max = max_element(A, N), min = min_element(A, N);
	int sorted = 0, range =	max - min + 1;
	int* counter = calloc(range, sizeof(int));

	for (int i = 0; i < N; ++i)
		counter[A[i] - min]++;

	for (int i = 0; i < range; ++i) {
		while (0 < counter[i]) {
			A[sorted++] = i + min;
			counter[i]--;
		}
	}

	//Free memory
	free(counter);
} //end-CountingSort
