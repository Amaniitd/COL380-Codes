#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include "stdbool.h"

// Partial code of Peterson algorithm

// To make compiler not rearrange the sequence, we are using flush here.

int main(int argc, char *argv[])
{
    int n = 5;
    int myID;
    bool ready[n];
    int defer = myID;
#pragma omp parallel num_threads(n)
    {
        // This block of code is executed by each of n threads
        myID = omp_get_thread_num();
        ready[myID] = true;
#pragma omp flush(ready, defer) // flush needs modified ready and unmodified defer ==> compiler will not rearrange ready and defer.
        defer = myID;
    }
}