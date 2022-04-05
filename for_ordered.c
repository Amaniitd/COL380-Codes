#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// int max(int res, int val) { return (val > res) ? val : res; }

// #pragma omp declare reduction(mymax:int \
//                               : omp_out = max(omp_out, omp_in)) initializer(omp_priv = INT_MIN)

void orderInsensitivePart1(int item)
{
    // printf("%s", "hii");
    // printf("%d", item);
}

void orderInsensitivePart2(int item)
{
    // printf("%s", "bye");
    // printf("%d", item);
}

void doThisInOrder(int item)
{
    printf("%d", item);
}

int main(int argc, char *argv[])
{
    int n = 5;
    int N = 20;
    int k = 0;
#pragma omp parallel num_threads(n)
#pragma omp for ordered
    for (int item = 0; item < N; item++)
    {
        orderInsensitivePart1(item); // Concurrent with other iterations
#pragma omp ordered
        doThisInOrder(item);         // Called with item = 0 to N-1, in that order
        orderInsensitivePart2(item); // Concurrent with other iterations
    }

    printf("%d", k);
}
