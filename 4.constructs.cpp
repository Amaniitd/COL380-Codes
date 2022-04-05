#include <stdio.h>
#include <omp.h>

// Let's say we don't want numt to be assigned 4 times. What should we do?

// int main(int argc, char *argv[])
// {
// 	int numt, tid;
// 	#pragma omp parallel private(tid) shared(numt)
// 	{
// 		//get the total number of OMP threads
// 		numt = omp_get_num_threads();

// 		//get the thread id of this thread
// 		tid = omp_get_thread_num();

// 		for (int i = 0; i < 100000; i++);  //introducing wait to see private variable

// 		printf("Hello World from thread %d of %d.\n", tid, numt);
// 	}
// 	return 0;
// }







// We can use barrier to to that.

// int main(int argc, char *argv[])
// {
// 	int numt, tid;

// 	#pragma omp parallel private(tid) shared(numt)
// 	{
// 		tid = omp_get_thread_num();

// 		if (tid == 0) {
// 			numt = omp_get_num_threads();
// 		}

// 		#pragma omp barrier

// 		printf("Hello World from thread %d of %d.\n", tid, numt);
// 	}

// 	return 0;
// }







// Better use single construct

int main(int argc, char *argv[])
{
	int numt, tid;

	#pragma omp parallel
	{
		#pragma omp single       //only one of any thread will execute this code
		{
			numt = omp_get_num_threads();
		} //implicit barrier here. can use nowait if we don't want any implicit barrier

		tid = omp_get_thread_num();

		printf("Hello World from thread %d of %d.\n", tid, numt);
	}

	return 0;
}








// Let's see master construct in which only master can execute that code

// int main(int argc, char *argv[])
// {
// 	int numt, tid;

// 	#pragma omp parallel
// 	{
// 		#pragma omp master      //only master thread will execute this code
// 		{
// 			numt = omp_get_num_threads();
// 		}                       // no implicit barrier here

// 		tid = omp_get_thread_num();

// 		printf("Hello World from thread %d of %d.\n", tid, numt);
// 	}

// 	return 0;
// }


