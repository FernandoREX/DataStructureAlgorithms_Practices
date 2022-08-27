#include <stdio.h>

#include <stdlib.h>
// para rand()

#include <time.h>

#include <omp.h>

#define TAM 25

void print( int x[], int n, char* msg )
{
  for( int i = 0; i < n; ++i ){
    printf( "%s[%d] = %d\n", msg, i, x[ i ] );
  }
}


int main()
{
  int a[TAM];
  for( size_t i = 0; i < TAM; ++i ){ a[ i ] = rand() % TAM; }
  int max = a[ 0 ];

  #pragma omp parallel for default( none ) shared( a, max ) num_threads( 4 )
    for( size_t i = 1; i < TAM; ++i ){
      if( a[ i ] > max ){

#if 0
        #pragma omp critical
        {
          if( a[ i ] > max ){
            max = a[ i ];
          }
        }
        printf( "(%d): %d\n", omp_get_thread_num(), max );
#else
        max = a[ i ];
        printf( "(%d): %d\n", omp_get_thread_num(), max );
#endif
      }
    } // --- Implicit barrier
  print( a, TAM, "a" );
  printf( "El valor máximo es: %d\n", max );
}
