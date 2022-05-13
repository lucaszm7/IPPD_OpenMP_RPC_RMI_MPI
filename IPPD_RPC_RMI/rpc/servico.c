#include <stdio.h>
#include "fibo.h"

unsigned int fibo_r(unsigned int n)
{
   if (n < 2) return n;
   else return (fibo_r(n-1) + fibo_r(n-2));
}

/* implementação da função fibo */
unsigned int * fibo_1_svc(unsigned int *argp, struct svc_req *rqstp)
{
   static unsigned int result;
 
   printf ("Recebi chamado: Fibo(%u)\n", *argp);
   result = fibo_r(*argp);
   return (&result);
}


