/*
 * 17/02/20
 */

#include <stdlib.h>
#include <stdio.h>


/**
 * @brief Imprime una lista de valores enteros.
 *
 * @param list La lista de números enteros.
 * @param tam El número de elementos en la lista.
 * @param msg Un mensaje de texto explicativo.
 */
void print( int* list, size_t tam, char* msg )
{
	printf( "%s", msg );
	for( size_t i = 0; i < tam; ++i ){
		printf( "%d, ", list[ i ] );
	}
	printf( "\n" );
}

/**
 * @brief Ordena en forma ascendente una lista de valores enteros utilizando al algoritmo counting sort.
 *
 * @param list[] La lista de números enteros
 * @param elems  El número de elementos en la lista.
 * @param low    Índice al primer elemento de la lista.
 * @param high   Índice al último elemento de la lista.
 */
void Countingsort( int list[], size_t elems, size_t low, size_t high )
{
   size_t capacity = 0;
   // calcula capacity

   int* aux = calloc( capacity, sizeof( int ) );
   // crea el arreglo auxiliar para enteros y lo inicializa a ceros.
   // En tu código usa a aux con notación normal de arreglo, aux[]


   // escribe aquí tu código. 

   free( aux );
   // devuelve la memoria del arreglo auxiliar
}

#define NUM_ELEMS 7

int main()
{
	int list[ NUM_ELEMS ] = { 1, 4, 4, 2, 7, 5, 2 };

	print( list, NUM_ELEMS, "  Antes: " );

	Countingsort( list, NUM_ELEMS, 0, 7 );
   // no existe ningún elemeno 0 en la lista, pero así es más fácil

	print( list, NUM_ELEMS, "Después: " );
}

