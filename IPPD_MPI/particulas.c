#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

struct Particula
{
    char c;
    double d[6];
    char b[7];
};

int main(int argc, char *argv[]) {
    struct Particula vet[1000];
    int myrank, worldSize;
    MPI_Status st;
    MPI_Datatype Particula_t;
    MPI_Datatype types[3] = { MPI_CHAR, MPI_DOUBLE, MPI_CHAR };
    int blocklen[3] = { 1, 6, 7 };
    MPI_Aint disp[3];
 
    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &worldSize);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    printf("World size is: %d\n", worldSize);
    printf("My rank is: %d\n", myrank);

    disp[0] = (int)(&vet[0].c) - (int)&vet[0];
    disp[1] = (int)(&vet[0].d) - (int)&vet[0];
    disp[2] = (int)(&vet[0].b) - (int)&vet[0];
    MPI_Type_create_struct(3, blocklen, disp, types, &Particula_t);
    MPI_Type_commit(&Particula_t);
 
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
 
    if( myrank == 0 )
    {
        printf("Waiting for receive...\n");
        MPI_Recv(vet, 1000, Particula_t, 1, 123, MPI_COMM_WORLD, &st);
        printf("received!!!\n");

    }
    else if (myrank == 1)
    {
        printf("Waiting for send...\n");
        MPI_Ssend(vet, 1000, Particula_t, 0, 123, MPI_COMM_WORLD);
        printf("Sended!!!\n");
    }
    
    MPI_Finalize();
    return 0;
}

