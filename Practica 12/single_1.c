#include <stdio.h>

#include <stdlib.h>
// para system() y rand()

#include <time.h>
// para time()

#include <omp.h>

#define TAM 10

int main(){

  int a[TAM];
  int b[TAM];

  srand( time( NULL ) );

  #pragma omp parallel num_threads( 4 )
  {
    //#pragma omp single // hilo unico
    {
      printf( "Thread %d\n", omp_get_thread_num() );

      for( size_t i = 0; i < TAM; ++i ){
        a[ i ] = rand() % 100;
        printf( "a[%ld] = %d\n", i, a[i] );
      }
    }

    #pragma omp for // imprimen los 4 hilos
      for( size_t i = 0; i < TAM; ++i ){
        b[ i ] = a[ i ] * 2;
      }

    //#pragma omp single // hilo unico
    {
      for( size_t i = 0; i < TAM; ++i ){
        printf( "Thread(%d): b[%ld] = %d\n", omp_get_thread_num(), i, b[i] );
      }
    }

  }
  return 0;
}

/*
single encarga la tarea a un solo nucleo
*/
