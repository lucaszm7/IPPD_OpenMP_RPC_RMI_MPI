/* Arquivo client.c: um cliente RPC simples */
 
#include <stdio.h>
#include "fibo.h"
 
/* função que chama a RPC fibo */
int fibo (CLIENT *clnt, unsigned int n)
{
   int *result;
   /* chama a função remota */
   result = fibo_1(&n,clnt);
   if (result == NULL)
   {
     printf ("Problemas ao chamar a função remota\n");
     exit (1);
   }
   return (*result);
}

 
int main( int argc, char *argv[])
{
   CLIENT *clnt;
   int n;
 
   /* verifica se o cliente foi chamado corretamente */
   if (argc!=3)
   {
      fprintf (stderr,"Usage: %s hostname n \n",argv[0]);
      exit (1);
   }
 
   /* cria uma struct CLIENT que referencia uma interface RPC */
   clnt = clnt_create (argv[1], FIBO_PROG, FIBO_VERSION, "udp");
 
   /* verifica se a referência foi criada */
   if (clnt == (CLIENT *) NULL)
   {
      clnt_pcreateerror (argv[1]);
      exit(1);
   }
 
   /* obtém os dois inteiros que serão passados via RPC */
   n = atoi(argv[2]);
 
   /* executa os procedimentos remotos */
   printf ("Fibo(%u) = %u\n", n, fibo(clnt,n));

   return (0);
}

