// no privado
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main()
{
  int i; // variable compartida en una región paralela (cuenta como global)

#pragma omp parallel num_threads( 4 ) // no privado
//#pragma omp parallel num_threads( 4 ) private( i ) // privado
{

  //int i; // esto tambien es volverla privada

  printf( "\n" );
  for( i = 0; i < 10; ++i ){
    printf( " %d ", i );
  }

}
  printf( "\n" );
}
