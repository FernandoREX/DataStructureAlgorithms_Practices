#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define ROWS_A 3
#define COLS_A 3

#define ROWS_B 3
#define COLS_B 2

#define ROWS_C 3
#define COLS_C 2

void Print_Matrix( int x[][COLS_C], size_t n, size_t m, char* text )
{
  printf( "--- %s\n", text );

  for( size_t i = 0; i < n; ++i ){
    for( size_t j = 0; j < m; ++j ){
      printf( "%d ", x[i][j] );
    }
    printf( "\n" );
  }
  printf( "\n" );
}

int main()
{
  int a[ROWS_A][COLS_A] =
  {
    { 1, 2, 3 },
    { 4, 5, 6 },
    { 7, 8, 9 },
  };

  int b[ROWS_B][COLS_B] =
  {
    { 1, 2 },
    { 3, 4 },
    { 5, 6 },
  };

  int c[ROWS_C][COLS_C];

  for( size_t i = 0; i < ROWS_A; ++i ){
    for( size_t j = 0; j < COLS_A; ++j ){
      printf( "%d ", a[i][j] );
    }
    printf( "\n" );
  }
  printf( "\n" );

  for( size_t i = 0; i < ROWS_B; ++i ){
    for( size_t j = 0; j < COLS_B; ++j ){
      printf( "%d ", b[i][j] );
    }
    printf( "\n" );
  }
  printf( "\n" );

  #pragma omp parallel for firstprivate(a,b)
  for (size_t i = 0; i < COLS_A; i++) {
    for (size_t j = 0; j < COLS_B; j++) {
      int suma = 0;
      for (size_t k = 0; k < COLS_A; k++) {
        suma += *((int*) a+j *COLS_A + k) * *((int*) b+k *COLS_B +i);
      }
      c[j][i] = suma;
    }
  }

  for( size_t i = 0; i < ROWS_C; ++i ){
    for( size_t j = 0; j < COLS_C; ++j ){
      printf( "%d ", c[i][j] );
    }
    printf( "\n" );
  }
  printf( "\n" );
}
