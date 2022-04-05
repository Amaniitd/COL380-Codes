#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int n = 500;
    int count = 0;
    omp_lock_t counter;
    omp_init_lock(&counter);
#pragma omp parallel num_threads(n)
    {
        // This block of code is executed by each of n threads
        while (!omp_test_lock(&counter))
        {
            // loop till counter isn't successfully locked.
        }
        count = count + 1;
        omp_unset_lock(&counter);  // unlock the counter
    }
    omp_destroy_lock(&counter);
    printf("%d", count);
}