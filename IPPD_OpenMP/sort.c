#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <pthread.h>
#include <time.h>
 
void bucketSort(int *arr, int n)
{
    if (n <= 1) return;
    if (n == 2 )
    {
        int aux;
        if (arr[1] < arr[0])
        {
            aux = arr[0];
            arr[0] = arr[1];
            arr[1] = aux;
        }
        return;
    }

    int l[n]; 
    int t[n]; 

    float m = 0;
    #pragma omp parallel for reduction(+:m)
    for(int i = 0; i < n; ++i)
        m += arr[i];
    m /= n;

    int nl = 0, nt = 0;
    for (int i = 0; i < n; ++i)
    {
        if (arr[i] < m)
        {
            l[nl] = arr[i];
            nl++;
        }
        else
        {
            t[nt] = arr[i];
            nt++;
        }
    }

    if (nl == 0 || nt == 0)
        return;

    #pragma omp task shared(l) firstprivate(nl)
    bucketSort(l, nl);

    #pragma omp task shared(t) firstprivate(nt)
    bucketSort(t, nt);

    #pragma omp taskwait

    for (int i = 0; i < nl; ++i)
        arr[i] = l[i];

    for (int i = nl; i < (nl + nt - 1); i++)
        arr[i] = t[i - nl];

    return;
}
 
int main(int argc, char** argv)
{
    if(argc < 3)
    {
        printf("===================================\n");
        printf("1. Parametro: Tamanho do vetor\n");
        printf("2. Parametro: Numero de threads\n");
        printf("===================================\n");
        return -1;
    }   

    int n = atoi(argv[1]);
    omp_set_num_threads(atoi(argv[2]));
    int arr[n];

    srand(time(NULL));
    for(int i = 0; i < n; ++i)
    {
        arr[i] = rand() % 100+1;
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    arr[0] = 2;
    arr[1] = 2;
    arr[2] = 2;

    #pragma omp parallel shared(arr)
    {
        #pragma omp single 
        bucketSort(arr, n);
    }


    printf("===============\n");
    printf("Sorted array is\n");
    printf("===============\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d, ", arr[i]);
    }
    return 0;
}