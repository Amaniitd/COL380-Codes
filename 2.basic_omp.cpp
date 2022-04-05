// Getting the number of threads and thread id

#include <stdio.h>
#include <omp.h>      //include header file

int main(int argc, char *argv[])
{
	#pragma omp parallel
	{
		//get the total number of OMP threads
		int numt = omp_get_num_threads();

		//get the thread id of this thread
		int tid = omp_get_thread_num();

		printf("Hello World from thread %d of %d.\n", tid, numt);
	}
	return 0;
}


// In the above program numt and tid are local variables. Let's see the next program which has shared variables
// This will lead to race conditions.

// int main(int argc, char *argv[])
// {
// 	int numt, tid;

// 	#pragma omp parallel
// 	{
// 		//get the total number of OMP threads
// 		numt = omp_get_num_threads();

// 		//get the thread id of this thread
// 		tid = omp_get_thread_num();

// 		printf("Hello World from thread %d of %d.\n", tid, numt);
// 	}
// 	return 0;
// }



