#include <stdio.h>
#include <omp.h>

#define SIZE 1000000000
int a[SIZE];

// int main(int argc, char *argv[])
// {
// 	int sum = 0;
// 	double t1, t2;

// 	for (int i = 0; i < SIZE; i++) {
// 		a[i] = 1;
// 	}

// 	t1 = omp_get_wtime();

// 	#pragma omp parallel
// 	{
// 		int psum = 0;

// 		#pragma omp for
// 		for (int i = 0; i < SIZE; i++) {
// 			psum += a[i];;
// 		}

// 		#pragma omp atomic
// 		sum += psum;
// 	}

// 	t2 = omp_get_wtime();

// 	printf("Sum of array of elements are %d. Time Taken = %g.\n", sum, t2 - t1);

// 	return 0;
// }







// Note: Cache Coherence problem will occur
// if sum is updated in the loop critically
// Code given below

// int main(int argc, char *argv[])
// {
// 	int sum = 0;
// 	double t1, t2;

// 	for (int i = 0; i < SIZE; i++) {
// 		a[i] = 1;
// 	}

// 	t1 = omp_get_wtime();

// 	#pragma omp parallel
// 	{

// 		#pragma omp for
// 		for (int i = 0; i < SIZE; i++) {
// 			#pragma omp atomic
// 			sum += a[i];
// 		}
// 	}

// 	t2 = omp_get_wtime();

// 	printf("Sum of array of elements are %d. Time Taken = %g.\n", sum, t2 - t1);

// 	return 0;
// }







// Instead of manually doing psum for each thread, we can use reduction

// int main(int argc, char *argv[])
// {
// 	int sum = 0;
// 	double t1, t2;

// 	for (int i = 0; i < SIZE; i++) {
// 		a[i] = 1;
// 	}

// 	t1 = omp_get_wtime();

// 	#pragma omp parallel reduction(+:sum)
// 	{
// 		#pragma omp for
// 		for (int i = 0; i < SIZE; i++) {
// 			sum += a[i];
// 		}
// 	}

// 	t2 = omp_get_wtime();

// 	printf("Sum of array of elements are %d. Time Taken = %g.\n", sum, t2 - t1);

// 	return 0;
// }







// we can use for clause

int main(int argc, char *argv[])
{
	int sum = 0;
	double t1, t2;

	for (int i = 0; i < SIZE; i++) {
		a[i] = 1;
	}

	t1 = omp_get_wtime();

	#pragma omp parallel for reduction(+:sum)
	for (int i = 0; i < SIZE; i++) {
		sum += a[i];
	}

	t2 = omp_get_wtime();

	printf("Sum of array of elements are %d. Time Taken = %g.\n", sum, t2 - t1);

	return 0;
}





