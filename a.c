#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
int max(int res, int val) { return (val > res) ? val : res; }

#pragma omp declare reduction(mymax:int \
                              : omp_out = max(omp_out, omp_in)) initializer(omp_priv = INT_MIN)

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000* number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}

void orderInsensitivePart1(int item)
{
    // printf("%s", "hii");
    // printf("%d", item);
}

void bar(int item)
{
    // printf("%s", "bye");
    delay(1000);
    printf("\n%d", item);
}

void foo(int item)
{
    delay(1000);
    printf("\n%d", item);
}

int main(int argc, char *argv[])
{
    int n = 20;
    int N = 20;
    int k = 0;

#pragma omp parallel
#pragma omp single nowait
    while (n--)
    {
#pragma omp task firstprivate(n)
        foo(n);

#pragma omp task firstprivate(n)
        bar(n);
    
    }
}
