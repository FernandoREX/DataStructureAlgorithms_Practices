#include <stdio.h>
#include <stdlib.h>

int fibo(int n, int* table){
  if (n < 2){
    table[n] = 1;
    return table[n];
  }
  if(table[n] != 0){ return table[n]; }

  int i,j;
  #pragma omp task shared(i) firstprivate(n,table) // parte la mitad del ciclo de recursion
    i = fibo(n-1, table);

  #pragma omp task shared(j) firstprivate(n, table) // parte la mitad del ciclo de recursion
    j = fibo(n-2, table);

  #pragma omp taskwait // hace que los nucleos que terminan esperen a los demas
  {
    table[n] = i+j;
    return i+j;
  }
}

int main(){
  int n = 8;
  int val[50];
  for (size_t i = 0; i < 49; i++) {
    val[i] = 0;
  }

  #pragma omp parallel shared(n,val)
  {
    #pragma omp master // tipo single
      val[n] = fibo(n,val);
  }
  printf("resultado: %d\n", val[n]);

  for (size_t i = 0; i < n+1; i++) {
    printf("%d\n", val[i]);
  }
}
