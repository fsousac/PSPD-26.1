#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int rank, size;
    int N;
    int valor = 0;
    int proximo, anterior;
    const int TAG_CONTAGEM = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc != 2) {
        if (rank == 0) {
            printf("Uso: mpirun -np <num_processos> ./programa <N>\n");
        }
        MPI_Finalize();
        return 1;
    }

    N = atoi(argv[1]);

    if (size < 2) {
        if (rank == 0) {
            printf("Execute com pelo menos 2 processos.\n");
        }
        MPI_Finalize();
        return 1;
    }

    if (N < 0) {
        if (rank == 0) {
            printf("Informe um N maior ou igual a 0.\n");
        }
        MPI_Finalize();
        return 1;
    }

    if (N < size) {
        if (rank == 0) {
            printf("Aviso: o enunciado supoe quantidade de processos menor que N.\n");
        }
    }

    proximo = (rank + 1) % size;
    anterior = (rank - 1 + size) % size;

    if (rank == 0) {
        printf("Processo %d imprimiu: %d\n", rank, valor);
        fflush(stdout);
        valor = 1;
        MPI_Send(&valor, 1, MPI_INT, proximo, TAG_CONTAGEM, MPI_COMM_WORLD);
    }

    while (1) {
        MPI_Recv(&valor, 1, MPI_INT, anterior, TAG_CONTAGEM, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        if (valor > N) {
            if (proximo != rank) {
                MPI_Send(&valor, 1, MPI_INT, proximo, TAG_CONTAGEM, MPI_COMM_WORLD);
            }
            break;
        }

        printf("Processo %d imprimiu: %d\n", rank, valor);
        fflush(stdout);

        valor++;
        MPI_Send(&valor, 1, MPI_INT, proximo, TAG_CONTAGEM, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
