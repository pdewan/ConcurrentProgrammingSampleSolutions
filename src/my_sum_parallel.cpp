#include <iostream>
#include <omp.h>

using namespace std;

void printSumWithTimes(int sum, int start, int end);
void printNumThreads();
void recordThreadIndex(int index);
void sum_parallel(double* array, int size) {
	cout << "sum_parallel\n";

	double start = omp_get_wtime();

	double sum = 0;


    #pragma omp critical
	{
	double sum = 0;
	}
    #pragma omp parallel
	{
		double local_sum = 0;

		int rank = omp_get_thread_num();
		int threads = omp_get_num_threads();

		int start_index = (size/threads)*rank;
		int end_index = (size/threads)*(rank+1);

		if(rank==threads-1)
			end_index=size;

		for(int i = start_index; i < end_index; i++) {
			local_sum += array[i];
			recordThreadIndex(i);
		}

		#pragma omp critical
		sum += local_sum;
	}

	double end = omp_get_wtime();

	printSumWithTimes(sum, start, end);


}
