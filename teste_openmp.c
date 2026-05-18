#include <stdio.h>
#include <omp.h>

int main() {
    omp_set_num_threads(10);
    printf("Imprimindo sequencial\n");
#pragma omp parallel
    {
        int thid, nthreads;
        thid = omp_get_thread_num();
        nthreads = omp_get_num_threads();
        printf("Hello World from %d/%d!\n", thid, nthreads);
    }

    printf("Imprimindo sequencial de novo\n");
#pragma omp parallel num_threads(3)
    {
        int thid, nthreads;
        thid = omp_get_thread_num();
        nthreads = omp_get_num_threads();
        printf("Hello World from %d/%d!\n", thid, nthreads);
    }
    printf("The end!\n");
    return 0;
}
