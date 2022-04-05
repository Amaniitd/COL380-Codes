// print hello world from multiple threads

#include <stdio.h>
#include <omp.h>      //include header file

int main(int argc, char *argv[])
{
	//specify the block to be executed in parallel
	#pragma omp parallel //This is a compiler directive. Use braces if more than one statements are to be executed in parallel
	{
		printf("Hello World\n");
	}
	return 0;
}

//Note - The above code is using default number of threads
//We can specify the number of threads by using the command $export OMP_NUM_THREADS=4 to change the number of threads



