#include <stdio.h>
#include <omp.h>      //include header file

// int main(int argc, char *argv[])
// {
// 	int numt, tid;

// 	#pragma omp parallel
// 	{
// 		//get the total number of OMP threads
// 		numt = omp_get_num_threads();

// 		//get the thread id of this thread
// 		tid = omp_get_thread_num();

// 		for (int i = 0; i < 100000; i++);  //introducing wait to see shared variable

// 		printf("Hello World from thread %d of %d.\n", tid, numt);
// 	}

// 	return 0;
// }


// fixing race conditon

int main(int argc, char *argv[])
{
	int numt, tid;

	#pragma omp parallel private(tid) shared(numt)
	{
		//get the total number of OMP threads
		numt = omp_get_num_threads();

		//get the thread id of this thread
		tid = omp_get_thread_num();

		for (int i = 0; i < 100000; i++);  //introducing wait to see private variable

		printf("Hello World from thread %d of %d.\n", tid, numt);
	}

	return 0;
}

