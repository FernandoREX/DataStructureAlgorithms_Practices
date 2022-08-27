#include <stdio.h>

#include <time.h>
// para el tiempo

#include <stdlib.h>
// para system()

#include <omp.h>

#define TAM 12

size_t fact( size_t n )
{
  if( n < 2 ) return 1;
  return n * fact( n - 1 );
}

int main()
{
  #pragma omp parallel for num_threads( 3 ) schedule( static, 2 )
  for( size_t i = 0; i < TAM; ++i ){
    printf( "(%d): Fact(%ld) = %ld\n", omp_get_thread_num(), i, fact( i ));
  } // --- Implicit barrier
}

/*
schedule hace que la carga de trabajo sea pareja en todos los hilos
*/
