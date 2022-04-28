#include <iostream>
#include <omp.h>

using namespace std;

//const int SIZE = 1000;
void printSumWithTimes(int sum, int start, int end);
void printNumThreads();
void recordThreadIndex(int index);
void add(double *p, int anIncrement) {
	*p += anIncrement;
}
void sum_parallel_for_reduction(double* array, int size) {
	cout << "sum_parallel_for_reduction\n";

	double start = omp_get_wtime();

	double sum = 0;
    #pragma omp  parallel for reduction ( + : sum )
//    #pragma omp  for reduction ( + : sum )

//	#pragma omp  for

	for (int i = 0; i < size; i++) {
//		sum += array[i];
		add(& sum, array[i] );
		recordThreadIndex(i);
	}

	double end = omp_get_wtime();

	printSumWithTimes(sum, start, end);

}
