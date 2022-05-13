#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv)
{
    printf("Hello World!!!\n");

    int myrank, worldSize;
    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &worldSize);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    printf("World size is: %d\n", worldSize);
    printf("My rank is: %d\n", myrank);

    MPI_Finalize();
    return 0;
}