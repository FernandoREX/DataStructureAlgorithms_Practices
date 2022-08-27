#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

#define TAM_LISTA 10 // para evitar magic numbers

typedef double Item; // redefinimos un tipo de dato

enum {ASCENDENTE, DESCENDENTE};

void swap(Item* x, Item* y)
{
    Item tmp = *x;
    *x = *y;
    *y = tmp;
}

void Burbuja_desc( Item lista[] , size_t num_elems)
{
  for(size_t Rondas = 0; Rondas < num_elems; Rondas++)
  {
    for(size_t elementos = 0; elementos < num_elems ; elementos++)
    {
      
      if(lista[elementos] < lista[elementos+1])
      {
          swap(&lista[elementos], &lista[elementos + 1]);
      }
    }
  }
}

void Burbuja_asc( Item lista[] , size_t num_elems)
{
  for(size_t Rondas = 0; Rondas < num_elems-1; Rondas++)
  {
    for(size_t elementos = num_elems-1; elementos > Rondas; elementos--)
    {
      if(lista[elementos] < lista[elementos-1])
      {
          swap(&lista[elementos], &lista[elementos - 1]);
      }
    }
  }
}

void Orden_Burbuja( Item lista[] , size_t num_elems, int direccion )
{
  if(direccion == ASCENDENTE)
  {
    Burbuja_asc( lista , num_elems);
  }
  else
  {
    Burbuja_desc(lista , num_elems );
  }
}

void print(Item list[])
{
  printf("\n[ ");
  for (size_t i = 0; i < TAM_LISTA; i++) 
  {
    printf("%g ", list[i]);
    if ( !(i == TAM_LISTA-1) )
    {
      printf(", ");
    }
  }
  printf(" ]\n");
}

int main()
{
  Item lista[TAM_LISTA] = {5.2,2.33,3.1,9.535,1.999,4.12,5.342,1.002,9.999,10.23,};
 
  print(lista);

  Orden_Burbuja(lista , TAM_LISTA , 1); 
  
  print(lista);
  return 0;
}
