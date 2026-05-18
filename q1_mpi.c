#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define MASTER 0

int main(int argc, char* argv[]) {
    int rank, nprocs;
    int tamvet;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    if (rank == MASTER) {
        printf("Tamanho do vetor: ");
        fflush(stdout);
        scanf("%d", &tamvet);
    }

    MPI_Bcast(&tamvet, 1, MPI_INT, MASTER, MPI_COMM_WORLD);

    int base = tamvet / nprocs;
    int resto = tamvet % nprocs;

    int chunk = base;
    if (rank < resto) {
        chunk++;
    }

    int* vlocal = (int*)malloc(chunk * sizeof(int));

    int* v = NULL;
    int* sendcounts = NULL;
    int* displs = NULL;

    if (rank == MASTER) {
        v = (int*)malloc(tamvet * sizeof(int));
        sendcounts = (int*)malloc(nprocs * sizeof(int));
        displs = (int*)malloc(nprocs * sizeof(int));

        for (int i = 0; i < tamvet; i++) {
            v[i] = (i + 1) * 10;
        }

        int desloc = 0;
        for (int i = 0; i < nprocs; i++) {
            sendcounts[i] = base;
            if (i < resto) {
                sendcounts[i]++;
            }

            displs[i] = desloc;
            desloc += sendcounts[i];
        }
    }

    MPI_Scatterv(
        v,
        sendcounts,
        displs,
        MPI_INT,
        vlocal,
        chunk,
        MPI_INT,
        MASTER,
        MPI_COMM_WORLD
    );

    printf("%d/%d: ", rank, nprocs);
    for (int i = 0; i < chunk; i++) {
        printf("%d ", vlocal[i]);
    }
    printf("\n");

    free(vlocal);

    if (rank == MASTER) {
        free(v);
        free(sendcounts);
        free(displs);
    }

    MPI_Finalize();

    return 0;
}