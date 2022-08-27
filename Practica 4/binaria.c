#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

size_t g_comparaciones=0;

void Quicksort(int list[], short first, short last){
  short x0 = first , x1 = last;
  short mid = (first+last)/2;
  int piv = list[mid];

  while(x0 <= x1){
    while (list[x0] < piv) {
      ++x0;
    }
    while (list[x1] > piv) {
      --x1;
    }
    if(x0 <= x1){
      int temp = list[x0];
      list[x0] = list[x1];
      list[x1] = temp;
      ++x0;
      --x1;
    }
  }
  if (first < x1){
    Quicksort(list, first, x1);
  }
  if (x0 < last){
    Quicksort(list, x0, last);
  }
}

bool BusquedaBinariaIT(int* lista, size_t tam, int llave){
  size_t inf = 0;
  size_t sup = tam-1;
  while(inf <= sup){
    size_t mid = (inf+sup)/2;
    ++g_comparaciones;
    if(lista[mid] == llave){
      return true;
    }
    else{
      if(llave < lista[mid]){
        if(inf == sup){
          return false;
        }else{
          sup = mid;
        }
      }else
        inf = mid+1;
    }
  }
  return false;
}

bool BusquedaBinariaRec(int* lista, size_t inf,size_t sup, int llave){
  size_t mid = (sup+inf)/2;

  ++g_comparaciones;

  if(lista[mid] == llave)
    return true;
  if(inf == sup)
    return false;
  if(lista[mid] > llave)
    return BusquedaBinariaRec(lista , inf , mid , llave);
  if(lista[mid] < llave)
    return BusquedaBinariaRec(lista , mid+1 , sup , llave);

  return false;
}

#define  TAM_LISTA 5000

int main(int argc, char const *argv[]) {
  int lista[TAM_LISTA];
  int llave;

  srand( time( NULL ) );

  for (size_t i = 0; i < TAM_LISTA; ++i) {
    if(i == TAM_LISTA-1){
      lista[i] = rand() % 10000;
      //llave = lista[i];
    }else
      lista[i] = rand() % 10000;
  }

  llave = rand() % 10000;
  Quicksort(lista,0,TAM_LISTA-1); // ordenar la lista

  //printf("\nEl valor %d %s", llave , BusquedaBinariaIT(lista,TAM_LISTA-1,llave) ? "Existe": "No existe");
  printf("\nEl valor %d %s", llave, BusquedaBinariaRec(lista,0,TAM_LISTA-1,llave) ? "Existe" : "No existe");

  printf("\nNumero de comparaciones: %ld\n", g_comparaciones);
  return 0;
}
