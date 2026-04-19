#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int rank, size;
    int N;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Informe o valor final N (contagem de 0 ate N): ");
        fflush(stdout);
        if (scanf("%d", &N) != 1) {
            fprintf(stderr, "Erro: nao foi possivel ler N.\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        // N = atoi(argv[1])

        if (N < 0) {
            fprintf(stderr, "Erro: N deve ser >= 0.\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        if (size > N + 1) {
            fprintf(stderr, "Erro: numero de processos de -np (%d) deve ser <= N + 1 (%d).\n", size, N + 1);
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
    }

    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Status status;

    for (int i = 0; i <= N; i++) {
        int owner = i % size;

        if (rank == owner && rank != 0) {
            MPI_Send(&i, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }

        if (rank == 0) {
            int value = i;
            if (owner != 0) {
                MPI_Recv(&value, 1, MPI_INT, owner, 0, MPI_COMM_WORLD, &status);
            }
            printf("%d ", value);
            fflush(stdout);
        }
    }

    if (rank == 0) {
        printf("\n");
        fflush(stdout);
    }

    MPI_Finalize();
    return 0;
}
