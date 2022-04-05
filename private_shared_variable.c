#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int l = 10, k = 11;
    int i;
    float j;
#pragma omp parallel firstprivate(k) private(l) shared(i, j)
    {
        // k is 11 but l is uninitialized
        // i and j are shared variable
    }
}