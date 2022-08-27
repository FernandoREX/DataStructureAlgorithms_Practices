#include <stdio.h>

#include <time.h>
// para el tiempo

#include <stdlib.h>
// para system()

#include <omp.h>

#define TAM 25

int main()
{
  #pragma omp parallel for num_threads( 4 ) //schedule( static, 1 )
    for( size_t i = 0; i < TAM; ++i ){
      printf( "(%d): i = %ld\n", omp_get_thread_num(), i );
    } // --- Implicit barrier
}
