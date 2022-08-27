#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char const *argv[]) {
  int acum = 0;
  int a[12] = {0,1,2,3,4,5,6,7,8,9,10,11};
  int n = 12;

  #pragma omp parallel for shared(a , n) //reduction(+ : acum)
  for(size_t i = 0; i < n; ++i) acum += a[i];

  printf("Resultado: %d\n", acum);

  return 0;
}

/*
reduction(+ : acum)
  -> evita que haya fallos en la ejecucion del programa
    Resultado: 15 -> Resultado: 45
    Resultado: 45 -> Resultado: 45
    Resultado: 45 -> Resultado: 45
    Resultado: 45 -> Resultado: 45
    Resultado: 40 -> Resultado: 45
    Resultado: 42 -> Resultado: 45
*/
