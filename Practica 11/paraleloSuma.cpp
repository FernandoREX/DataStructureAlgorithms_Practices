#include <stdio.h>

#include <stdlib.h>
// para la función rand()

#include <time.h>
// para inicializar la semilla de aleatoriedad

#include <omp.h>

void Imprime( int arr[], int tam )
{

#pragma omp parallel for num_threads( 4 )
  for(int i = tam; i > 0 ; --i){
    printf(" ( %d , %d ) ", omp_get_thread_num() ,arr[i-1] );
  }

  printf("\n");
}

// No vamos a usar esta función, pero está aquí para que se vea la
// diferencia con su contraparte paralela.
void suma_sec( int arr1[], int arr2[], int res[], int tam )
{
  for( int i = 0; i < tam; ++i ){
    res[ i ] = arr1[ i ] + arr2[ i ];
  }
}

void suma_par( int arr1[], int arr2[], int res[], int tam )
{
  int mitad = tam / 2;
  // para que este ejemplo funcione correctamente, 'tam' DEBE ser múltiplo
  // de 2
#pragma omp parallel num_threads( 4 )
{

  int id = omp_get_thread_num(); // obtenemos el id de este hilo

  int inicio = id * mitad;

  int fin = inicio + mitad;

  for( int i = inicio; i < fin; ++i ){
    //printf( "El hilo %d está calculando res[ %d ]\n", id, i );
    res[ i ] = arr1[ i ] + arr2[ i ];
  }

}

}

#define TAM 50

int main()
{
  int a[ TAM ];
  int b[ TAM ];
  int c[ TAM ];

  srand( time( NULL ) );

  for( int i = 0; i < TAM; ++i ){
    a[ i ] = rand() % 100;
    b[ i ] = rand() % 100;
  }

  suma_par( a, b, c, TAM );

  for( int i = 0; i < TAM; ++i ){
    //printf( "%2d) %d + %d = %d\n", i, a[ i ], b[ i ], c[ i ] );
  }

  Imprime(a , TAM);
}
