#include <stdio.h>
#include <stdlib.h>
// para la función rand()
#include <time.h>
// para inicializar la semilla de aleatoriedad
#include <omp.h>

void suma(int a, int b, int* resultado){
  int res = 0;

  while(a < b){
    res += a;
    printf("%d\n", res);
    ++a;
  }

  *resultado += res;
}

int main(){
  int max = 16;
  int resultado = 0;

#pragma omp parallel num_threads( omp_get_max_threads() )
{
  int nucleo = omp_get_thread_num();
  int inicio = omp_get_thread_num()*omp_get_max_threads();
  int final = (max*(nucleo+1))/omp_get_max_threads();
  suma( inicio ,final , &resultado);
}

  printf("la suma es: %d\n", resultado);
  return 0;
}
