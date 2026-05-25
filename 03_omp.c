#include <stdio.h>
#include <omp.h>
#define TAM 500000

int main()
{
    int thid, nthreads;
    int a[TAM], b[TAM], c[TAM];
    int i;

    for (int i = 0; i < TAM; i++)
    {
        a[i] = 1;
        b[i] = 1;
    }
    int soma = 0;
#pragma omp parallel 
    {
        int somalocal = 0;
#pragma omp for
        for (int i = 0; i < TAM; i++)
        {
            c[i] = a[i] + b[i];
            somalocal += c[i];
            // printf("c[%d]=%d\n", i, c[i]);
        }
#pragma omp critical
        soma += somalocal;
    }
    printf("Soma = %d\n", soma);
    return 0;
}
