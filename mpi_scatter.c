#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#define MASTER 0

int main(int argc, char* argv[]) {
    int rank, size;
    int dados[4] = { 13, 54, 1917, 321 };
    int dado_espalhado[2];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Scatter(&dados, 2, MPI_INT, &dado_espalhado, 2, MPI_INT, MASTER, MPI_COMM_WORLD);
    printf("Processo %d/%d recebeu %d %d\n", rank, size, dado_espalhado[0], dado_espalhado[1]);

    MPI_Finalize();
    return 0;
}
