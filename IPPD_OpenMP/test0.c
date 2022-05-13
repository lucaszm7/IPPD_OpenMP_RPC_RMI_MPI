#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

int fibo( int n ) {
    int r1, r2;
    if( n < 2 ) return n;
    #pragma omp task shared(r1) firstprivate(n)
    r1 = fibo(n-1);
    #pragma omp task shared(r2) firstprivate(n)
    r2 = fibo(n-2);
    #pragma omp taskwait
    return r1+r2;
}

int main(int argc, char **argv)
{
    #pragma omp parallel
    {
        printf("Eu sou o thread %d!\n", omp_get_thread_num());

        #pragma omp master
        printf("Eu sou o thread Master %d!\n", omp_get_thread_num());

        #pragma omp single
        printf("%d fui o thread a pegar essa tarefa!\n", omp_get_thread_num());

        #pragma omp sections
        {
            #pragma omp section
            {
                printf("A\n");    
            }
            #pragma omp section
            {
                printf("B\n");    
            }
            #pragma omp section
            {
                printf("C\n");    
            }
        }

        #pragma omp for schedule(static, 4)
        for(int i = 0; i < 80; ++i)
        {
            printf("Thread[%d] executando tarefa[%d]\n", omp_get_thread_num(), i);
        }
    }

    printf("Todos threads terminaram!\n");
    printf("Começando Tasks... %d\n", argc);

    if(argc < 2)
    {
        printf("===================================\n");
        printf("Valor para fibonacci nao passado!!!\n");
        printf("===================================\n");
        return -1;
    }    
    int n = atoi(argv[1]);
    int r;
    #pragma omp parallel shared(r, n)
    {
        #pragma omp single
        r = fibo(n);
    }
    printf("Fibo de %d = %d\n", n, r);
    return 0;
}