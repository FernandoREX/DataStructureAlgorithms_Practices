#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define TAM_LISTA 10

enum {
  ASCENDENTE = 0,
  DESCENDENTE = 1
};

void print(int list[])
{ // funcion que imprime los valores de una lista
  printf("\n[ ");
  for (size_t i = 0; i < TAM_LISTA; i++) 
  {
    printf("%d ", list[i]);
    if ( !(i == TAM_LISTA-1) ){
      printf(", ");
    }
  }
  printf(" ]\n");
}

void Merge(int lista[], size_t primero, size_t ultimo, int aux[], int direccion)
{
  size_t x0, x1, x2, x3, mid, index = primero; // creamos los valores a usar como indices
  mid = (primero + ultimo)/2; // ubicamos el punto medio de la lista recibida
  x0 = index; // inicio
  x1 = mid; // primera mitad
  x2 = mid+1; // segunda mitad
  x3 = ultimo; // fin del arreglo

  while(x0 <= x1 && x2 <= x3)
  { // mientras los indices no salgan del limite
    if(lista[x0] > lista[x2] && direccion == DESCENDENTE)
    {
      aux[index] = lista[x0];// cambiamos el indice con el valor mayor
      ++index;
      ++x0;
    }else if(lista[x0] < lista[x2] && direccion == ASCENDENTE)
    {
      aux[index] = lista[x0]; // cambiamos el indice con el valor menor
      ++index;
      ++x0;
    }else
    {
      aux[index] = lista[x2]; // este bloque de codigo se ejecuta en caso de que
      ++index; // el valor de las anteriores comprobaciones no corresponda
      ++x2;
    }
  }

  while(x0 <= x1)
  { // nuevamente recorremos y acomodamos
    aux[index] = lista[x0];
    ++index;
    ++x0;
  } // la primera mitad

  while(x2 <= x3)
  { // igual con la segunda mitad
    aux[index] = lista[x2];
    ++index;
    ++x2;
  }

  for (size_t i = primero; i < ultimo; ++i) 
  { // por ultimo
    lista[i] = aux[i]; // regresamos el valor del auxiliar a la lista principal
  }
}

void MergeSort(int lista[] , size_t primero , size_t ultimo , int aux[] , int direccion)
{
  if(primero < ultimo)
  { // checamos que los valores de los indices sean diferentes
    size_t mitad = (primero + ultimo)/2; // creamos el indice de la mitad
    // de izquierda a derecha va a checar la primera mitad e ira entrando nuevamente hasta llegar a un solo elemento
    MergeSort(lista, primero, mitad, aux, direccion); // partimos la lista a la mitad derecha
    // de izquierda a derecha va a checar la segunda mitad y hara lo mismo
    MergeSort(lista, mitad+1, ultimo, aux, direccion); // partimos la lista a la mitad izquierda
    // al llegar a un valor que se deba ordenar llama la funcion y ordena esa parte
    Merge(lista, primero, ultimo, aux, direccion); // mezclamos el resultado y regresamos a la funcion de invocacion
  }
}

void Ordenar(int lista[] , int num_elems , int direccion)
{
  int aux[num_elems]; 
  MergeSort(lista, 0, num_elems-1, aux, direccion);
}

int main(){
  int lista[TAM_LISTA] = {12,9,23,2,15,19,20,5,1,99};

  print(lista); // imprimimos la lista original

  Ordenar(lista , TAM_LISTA , ASCENDENTE); // ordenamos de manera

  print(lista); // imprimimos la lista final

  return 0;
}
