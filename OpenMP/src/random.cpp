#include <iostream>
#include <omp.h>
#include <stdlib.h>
#include <math.h>
//#include <unistd.h>
using namespace std;

const int NUMBER_OF_RANDOMS = 10;
const int NUMBER_OF_THREADS = 1;
struct ThreadIndices {
	int startIndex, endIndex;
};
ThreadIndices computeThreadIndices (int aStartIndex, int anEndIndex);


bool processIteration (int anIndex) {
	bool retVal;
	#pragma omp critical
	retVal = ((anIndex + 1) % (omp_get_thread_num() + 1) == 0);
	return retVal;
}


//void randoms(int* aRandomNumbers, int aNumberOfRandoms) {
//	{
//
//		ThreadIndices aThreadIndices = computeThreadIndices(0, aNumberOfRandoms);
//		#pragma omp critical
//		cout << "Thread:" << omp_get_thread_num()  << " allocated start index:" << aThreadIndices.startIndex << " and num end index: " << aThreadIndices.endIndex  << endl;
//		for (int anIndex = aThreadIndices.startIndex; anIndex < aThreadIndices.endIndex; anIndex++) {
//			aRandomNumbers[anIndex] = rand();
//		}
//	}
//}
void randoms(int aStartIndex, int anEndIndex) {
	srand(omp_get_thread_num());
	{
		for (int anIndex = aStartIndex; anIndex < anEndIndex; anIndex++) {
			cout << rand() << endl;
		}
	}
}

void printIntArray (int* anArray, int aStartIndex, int anEndIndex) {
//	ThreadIndices aThreadIndices = computeThreadIndices(0, aSize);
	cout << "Int Array:" << endl;
	for (int anIndex = aStartIndex; anIndex < anEndIndex; anIndex++) {
		cout << "Thread:" << omp_get_thread_num() << " Index:" << anIndex << " Value: " << anArray[anIndex] << endl;
	}
}
int slowMin (int anInt1, int anInt2) {
	cout << "Thread:" << omp_get_thread_num() << " calculating minimum of:" << anInt1 << " and " << anInt2 << endl;
	if (anInt1 > anInt2) {

//		sleep (10);
		cout << "Thread:" << omp_get_thread_num() << " returning:" << anInt2  << endl;

		return anInt2;
	}
	cout << "Thread:" << omp_get_thread_num() << " returning:" << anInt1  << endl;
	return anInt1;
}
void computeAndPrintRandom(int aNumberOfThreads) {
	int minRandomNumber = INT_MAX ;
	int aSeed;
	int aRandomNumber;

//	#pragma omp parallel private (aRandomNumber, aSeed) num_threads(aNumberOfThreads)

//	#pragma omp parallel private (aSeed) num_threads(aNumberOfThreads)

	#pragma omp parallel num_threads(aNumberOfThreads)
	{
		int aSeed;
//		#pragma omp_critical
		{
			aSeed = omp_get_thread_num(); // set of seed

//			#pragma omp_critical
			cout << "Seed for thread:" << omp_get_thread_num() << " is "<< aSeed << endl ;


			srand(aSeed); // use of seed
		}

//		aSeed = omp_get_thread_num();

		int aRandomNumber;
		aRandomNumber = rand();

//		#pragma omp critical
//		cout << "Thread:" << omp_get_thread_num() << " Random:" << aRandomNumber << endl;

		#pragma omp critical
//		minRandomNumber = min (aRandomNumber, minRandomNumber);
		minRandomNumber = slowMin (aRandomNumber, minRandomNumber);

//		allRandoms[omp_get_thread_num()] = aRandomNumber;

	}

	cout << "Min Random:" << minRandomNumber << endl;


}

void computeAndPrintRandoms(int aNumThreads) {
//	int aRandomNumbers[NUMBER_OF_RANDOMS];


//		int* aComputedRandomNumbers = new int[NUMBER_OF_RANDOMS];


	int aStartIndex = 0;
	int anEndIndex = NUMBER_OF_RANDOMS;

	#pragma omp parallel num_threads(aNumThreads)
	{
//		srand(omp_get_thread_num());

//		ThreadIndices aThreadIndices = computeThreadIndices (0, NUMBER_OF_RANDOMS);
//		int aStartIndex = aThreadIndices.startIndex;
//		int anEndIndex = aThreadIndices.endIndex;
//		#pragma omp critical
//		cout << "Thread:" << omp_get_thread_num()  << " allocated start index:" << aStartIndex << " and num end index: " << anEndIndex  << endl;

		#pragma omp for
		for (int anIndex = aStartIndex; anIndex < anEndIndex; anIndex++) {
			#pragma omp critical
			cout << "Thread:" << omp_get_thread_num() << " index:" << anIndex << " random: " <<  rand() << endl;
		}

//		randoms(aStartIndex, anEndIndex);
//		printIntArray(aRandomNumbers,  aStartIndex, anEndIndex);

	}

}
//void computeAndPrintRandomsSequential() {
//
//	int* aRandomNumbers = new int[NUMBER_OF_RANDOMS];
//
//	randoms(aRandomNumbers, NUMBER_OF_RANDOMS);
//
//	printIntArray(aRandomNumbers, 0,  NUMBER_OF_RANDOMS);
//
//}
//void copy (int* aFinalRandomNumbers, int* aComputedRandomNumbers, int aStartIndex, int anEndIndex) {
//	for (int anIndex = aStartIndex; anIndex < anEndIndex; anIndex++) {
//		aFinalRandomNumbers[anIndex] = aComputedRandomNumbers[anIndex];
//	}
//}
//void computeRandomsInParallelAndPrintRandoms(int aNumThreads) {
//	int aFinalRandomNumbers[NUMBER_OF_RANDOMS];
//	int aSeed;
//
//	#pragma omp parallel num_threads(aNumThreads)
//	{
//		int aComputedRandomNumbers[NUMBER_OF_RANDOMS];
//
////		#pragma omp_critical
////		{
////			aSeed = omp_get_thread_num();
////			#pragma omp critical
////			cout << "Seed for thread:" << omp_get_thread_num() << " is "<< aSeed << endl ;
////			srand(aSeed);
////		}
//		int aStartIndex = 0;
//		int anEndIndex = NUMBER_OF_RANDOMS;
//		ThreadIndices aThreadIndices = computeThreadIndices (0, NUMBER_OF_RANDOMS);
//		aStartIndex = aThreadIndices.startIndex;
//		anEndIndex = aThreadIndices.
////		#pragma omp critical
////		cout << "Thread:" << omp_get_thread_num()  << " allocated start index:" << aThreadIndices.startIndex << " and num end index: " <<  aThreadIndices.startIndex  << endl;
////		randoms(aComputedRandomNumbers, aThreadIndices.startIndex, aThreadIndices.endIndex);
//
////		copy (aFinalRandomNumbers, aComputedRandomNumbers, aThreadIndices.startIndex, aThreadIndices.endIndex );
//
//	}
//	printIntArray(aFinalRandomNumbers,  0, NUMBER_OF_RANDOMS);
//}



