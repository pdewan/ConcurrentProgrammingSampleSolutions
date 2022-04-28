#include <iostream>
#include <omp.h>

using namespace std;

void printSumWithTimes (int sum, int start, int end);
void printNumThreads();
void recordThreadIndex(int index);
void sum_parallel_for_local_var(double* array, int size)
{
	cout << "sum_parallel_for_local_var\n";

	double start = omp_get_wtime();

	double sum = 0;

	int a, b;
//
//	for (int i = 0; i < size; i++) {
//			sum += array[i];
//			recordThreadIndex(i);
//	}

//    #pragma omp parallel shared (sum, start) private (a, b)
	#pragma omp parallel

	{
		double local_sum = 0;

		#pragma omp for
		for(int i = 0; i < size; i++) {
			local_sum += array[i];
			recordThreadIndex(i);
		}

		#pragma omp critical
		sum += local_sum;
	}

	double end = omp_get_wtime();

	printSumWithTimes(sum, start, end);
	
}
