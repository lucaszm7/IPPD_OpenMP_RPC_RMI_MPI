/* Definição da interface */
 
#define PROGRAM_NUMBER 12345678
#define VERSION_NUMBER 1
 
/* Definição da interface que será oferecida aos clientes */
 
program FIBO_PROG
{
   version FIBO_VERSION
   {
     unsigned int FIBO (unsigned int) = 1;
   }
   = VERSION_NUMBER;
}
= PROGRAM_NUMBER;

