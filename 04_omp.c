#include <stdio.h>
#include <mpi.h>
#include <omp.h>

int main()
{
    int thid, nthreads;
    int rank, nprocs;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
#pragma omp parallel private(thid) shared(nthreads)
    {
        nthreads = omp_get_num_threads();
        thid = omp_get_thread_num();
        printf("Proc %d/%d, Thread %d/%d --> Ola Mundo!\n", rank, nprocs, thid, nthreads);
    }
    printf("Proc %d/%d --> Fora das threads... \n", rank, nprocs);
    return 0;
}
