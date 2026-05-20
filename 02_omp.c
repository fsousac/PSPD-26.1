#include <stdio.h>
#include <omp.h>
#define TAM 15

int main()
{
    int thid, nthreads, result = 0;
    // int v[TAM] = { 15,12,433,465,57,655,74,80 };
    int v[TAM];
    for (int i = 0; i < TAM; i++)
    {
        v[i] = 1;
    }


    // #pragma omp parallel private(thid) shared(nthreads,result, v) num_threads(12)
    //     {
    //         thid = omp_get_thread_num();
    // #pragma omp single
    //         nthreads = omp_get_num_threads();
    //         int local_soma = 0;
    // #pragma omp for
    //         for (int i = 0; i < TAM; i++)
    //         {
    //             printf("%d/%d says: v[%d] = %d\n", thid, nthreads, i, v[i]);
    //             local_soma += v[i];
    //         }
    // #pragma omp atomic
    //         result += local_soma;
    //     }


#pragma omp parallel for shared(v) reduction(+:result)
    for (int i = 0; i < TAM; i++)
    {
        result += v[i];
    }

    printf("Resultado final: %d\n", result);

    return 0;
}
