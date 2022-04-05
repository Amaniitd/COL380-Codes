//Computing sum of an array using task

#include <stdio.h>
#include <omp.h>

#define SIZE 1000000000
#define STEP_SIZE 1000
int a[SIZE];

int main(int argc, char *argv[])
{
	int sum = 0;
	double t1, t2;

	for (int i = 0; i < SIZE; i++) a[i] = 1;

	t1 = omp_get_wtime();

	#pragma omp parallel
	{
		#pragma omp for
		for (int i = 0; i < SIZE; i += STEP_SIZE) {

			int start = i;
			int end = i + STEP_SIZE - 1;

			#pragma omp task         //instead of doing this task by this thread, create a task and add it to task queue
			{
				int psum = 0;
				for (int j = start; j <= end; j++) {
					psum += a[j];
				}
				#pragma omp atomic
				sum += psum;
			}

		} // implicit barrier at the end of omp for

	} // implicit barrier at the end of omp parallel

	t2 = omp_get_wtime();
	printf("Sum of array of elements are %d. Time Taken = %g.\n", sum, t2 - t1);

	return 0;
}

// Note: Variables in the task refers to the variables of the thread which created it not the thread which runs it.
// Here, j, start and end variabls are treated as first private in the task.


// Tasks complete at any barriers. If we want all tasks to be finished by a point, we need to put barrier just above that point
// We can also omp taskwait to allow all tasks to be finished before proceeding further
// Both are different. taskwait waits for tasks spawned by this thread not for all tasks


// We could have created task using single thread. Instead of using omp for, use omp single or master.




