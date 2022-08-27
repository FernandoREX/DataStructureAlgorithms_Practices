#include<stdio.h>
#include<stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

size_t g_comparaciones = 0;

bool BusquedaLinealIT(int* list,size_t tam, int key){
  for (size_t i = 0; i < tam; ++i) {
    g_comparaciones++;
    if (list[i] == key) {
      return true;
    }
  }
  return false;
}

bool BusquedaLinealRE(int* list,size_t tam , size_t index , int key){
  g_comparaciones++;
  if(list[index] == key)
    return true;
  else if(index == tam)
    return false;
  else
    return BusquedaLinealRE(list,tam,++index,key);
}

#define TAM_LISTA 5000

int main(int argc, char const *argv[]) {
  int lista[TAM_LISTA];
  int llave;

  srand( time( NULL ) );

  for (size_t i = 0; i < TAM_LISTA; ++i) {
    if(i == TAM_LISTA-1){
      lista[i] = rand() % 10000;
      //llave = lista[i];
    }else{
      lista[i] = rand() % 10000;
    }
  }

  llave = rand() % 10000;
  // Quicksort(lista,0,TAM_LISTA-1);

  printf("%d %s\n", llave , BusquedaLinealIT(lista,TAM_LISTA,llave) ? "Existe en la lista" : "No existe en la lista");
  //printf("%d %s\n", llave , BusquedaLinealRE(lista,TAM_LISTA,0,llave) ? "Existe en la lista" : "No existe en la lista");
  printf("numero de comparaciones: %ld\n", g_comparaciones);
  return 0;
}
