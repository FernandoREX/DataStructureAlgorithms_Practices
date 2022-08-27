#include <stdio.h>

#include <stdlib.h>
// para system() y rand()

#include <omp.h>

#define TAM 10

int main()
{
int cont = 0, b = 0, i , n = 50;

  #pragma omp parallel for num_threads( 4 ) shared( n, cont, b) private( i )
  for( i = 0; i < n; ++i ){

    #pragma omp atomic
    cont += i; //cont += b; edit lab 2 //++; edit lab 1

    #pragma omp atomic // add lab
    b++;// add lab

  } // --- Implicit barrier

  printf("cont = %d , b = %d\n", cont,b);
}

/*
atomic protege lo que se encuentre a la izquierda
atomic se aplica a instrucciones simples
*/
