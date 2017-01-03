#include "Sorting.h"
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <stdlib.h>

unsigned N;

void Test(void (*F)(int *, const unsigned), const char *msg) {
    int A[N], min = INT_MAX, max = 0;

    //Generate random array
    srand (time(NULL));
    for (int i = 0; i < N; ++i){
        A[i] = rand();
        if (A[i] < min)
            min = A[i];
        else if (A[i] > max)
            max = A[i];
    }

    //Run sorting algorithm
    printf("Using %s to sort %d numbers...\n", msg, N);
    clock_t start, end;
    start = clock();
    F(A, N);
    end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Took %f seconds.\n", cpu_time_used);

    //Check the result
    if (A[0] != min || A[N - 1] != max) return;
    for (int i = 1; i < N; ++i) {
        if (A[i - 1] > A[i]) {
        	printf("Array is not sorted!");
            return;
        }
    }
    return;
}

int main(int argc, char* argv[]) {
	printf("Enter array size: ");
    scanf("%d", &N);
    Test(BubbleSort, "Bubble Sort");
    Test(SelectionSort, "Selection Sort");
    Test(InsertionSort, "Insertion Sort");
    Test(MergeSort, "Merge Sort");
    Test(QuickSort, "Quick Sort");
    Test(HeapSort, "Heap Sort");
    Test(RadixSort, "Radix Sort");
    Test(CountingSort, "Counting Sort");
    return 0;
}
