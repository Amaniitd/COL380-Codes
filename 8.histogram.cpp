//Given list of integers
//Find the number of occurrences of each integer

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include<time.h>

#define INP_SIZE (1 << 26)
#define HRR_SIZE (1 << 20)

int hist[HRR_SIZE];
int inp[INP_SIZE];

// int main(int argc, char const *argv[])
// {
// 	int i, key;
// 	double t1, t2;

// 	for (i = 0; i < HRR_SIZE; i++) hist[i] = 0;

// 	srand(time(0));
// 	for (i = 0; i < INP_SIZE; i++) inp[i] = rand() % HRR_SIZE;

// 	t1 = omp_get_wtime();

// 	#pragma omp parallel for private(key)
// 	for (i = 0; i < INP_SIZE; i++)
// 	{
// 		key = inp[i];

// 		#pragma omp critical
// 		hist[key]++;
// 	}

// 	t2 = omp_get_wtime();

// 	printf("Time Taken = %g.\n", t2 - t1);

// 	return 0;
// }



// The above code is coarse grained as we need to provide mutual exclusion to all
// indices of the histogram. But, we are providing mutual exclusion even to the
// access of two different indices of histogram. In this case our code is running
// slower than the sequential code.







// providing fine grained locking by using locks
// omp_lock_t lock[HRR_SIZE];

// int main(int argc, char const *argv[])
// {
// 	int i, key;
// 	double t1, t2;

// 	for (i = 0; i < HRR_SIZE; i++) {
// 		hist[i] = 0;
// 		omp_init_lock(&lock[i]);
// 	}

// 	srand(time(0));
// 	for (i = 0; i < INP_SIZE; i++) {
// 		inp[i] = rand() % HRR_SIZE;
// 	}

// 	t1 = omp_get_wtime();

// 	#pragma omp parallel for private(key)
// 	for (i = 0; i < INP_SIZE; i++)
// 	{
// 		key = inp[i];

// 		omp_set_lock(&lock[key]);
// 		hist[key]++;
// 		omp_unset_lock(&lock[key]);
// 	}

// 	t2 = omp_get_wtime();

// 	for (i = 0; i < HRR_SIZE; i++) {
// 		omp_destroy_lock(&lock[i]);
// 	}

// 	printf("Time Taken = %g.\n", t2 - t1);

// 	return 0;
// }











// We can use omp atomic which provides mutual exclusion for a particular memory location
// not for the code that follows this directive


int main(int argc, char const *argv[])
{
	int i, key;
	double t1, t2;

	for (i = 0; i < HRR_SIZE; i++) hist[i] = 0;

	srand(time(0));
	for (i = 0; i < INP_SIZE; i++) inp[i] = rand() % HRR_SIZE;

	t1 = omp_get_wtime();

	#pragma omp parallel for private(key)
	for (i = 0; i < INP_SIZE; i++)
	{
		key = inp[i];

		#pragma omp atomic
		hist[key]++;
	}

	t2 = omp_get_wtime();

	printf("Time Taken = %g.\n", t2 - t1);

	return 0;
}









