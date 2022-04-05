#include <stdio.h>
#include <omp.h>

#define SIZE 100000000
int A[SIZE];
int B[SIZE];

int dot_product(int* A, int* B, int n)
{
	int dot = 0;

	#pragma omp parallel for reduction(+:dot)
	for (int i = 0; i < n; i++) {
		dot += A[i] * B[i];
	}

	return dot;
}

int main(int argc, char const *argv[])
{
	int dot = 0;
	double t1, t2;

	for (int i = 0; i < SIZE; i++) {
		A[i] = 1;
		B[i] = 1;
	}

	t1 = omp_get_wtime();
	dot = dot_product(A, B, SIZE);
	t2 = omp_get_wtime();

	printf("Dot product is %d. Time Taken = %g.\n", dot, t2 - t1);

	return 0;
}









