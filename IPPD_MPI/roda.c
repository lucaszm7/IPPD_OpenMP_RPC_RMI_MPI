#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
 int worldSize, myRank, aux, dest;
 MPI_Status st;

 MPI_Init(NULL, NULL);  // Inicialização

 MPI_Comm_size(MPI_COMM_WORLD, &worldSize); // Quantos processos envolvidos?
 MPI_Comm_rank(MPI_COMM_WORLD, &myRank); // Meu identificador

    printf("Has %d processor\n", worldSize);
    printf("My rank is: %d\n", myRank);

 if( worldSize == 1 ) aux = 0;
 else {
  if( myRank == 0 ) { // Sou o primeiro no mundo!!!
   MPI_Ssend((void*)&myRank,1,MPI_INT,myRank+1, 0, MPI_COMM_WORLD);
   MPI_Recv(&aux,1,MPI_INT,worldSize-1,MPI_ANY_TAG,MPI_COMM_WORLD, &st);
   printf("Soma dos Ranks: %d\n",aux+myRank);
  } else {
   dest = (myRank == worldSize-1) ? 0 : myRank+1;
   MPI_Recv(&aux,1,MPI_INT,myRank-1,MPI_ANY_TAG,MPI_COMM_WORLD, &st);
   printf("Eu %d recebi o rank: %d\n", myRank, aux);
   aux += myRank;
   MPI_Ssend(&aux,1,MPI_INT, dest, 0, MPI_COMM_WORLD);
  }
 }
   
 MPI_Finalize(); // Finalização
}

