#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


int max(int res, int val) { return (val > res) ? val : res;}

// a reduction operation "mymax" is defined here.
#pragma omp declare reduction(mymax:int:omp_out = max(omp_out, omp_in)) initializer(omp_priv = INT_MIN)


int main(int argc, char *argv[])
{
    int n = 5;

    int k = 0;
#pragma omp parallel reduction(mymax: k) num_threads(12)
    k = omp_get_thread_num();
// k is theread number in each thread 
// k is reduced with the help of mymax value ==> max(prev_value_of_k, new_value_of_k)
    printf("%d", k);
}