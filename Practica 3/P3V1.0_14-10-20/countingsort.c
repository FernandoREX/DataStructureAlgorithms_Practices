#include <stdlib.h>
#include <stdio.h>

int g_contador=0;

void print( int* list, size_t tam, char* msg )
{
	printf( "%s [ ", msg );
	for( size_t i = 0; i < tam; ++i ){
		if(i == tam-1)
			printf("%d ]\n", list[i] );
		else
			printf( "%d, ", list[ i ] );
	}
	printf( "\n" );
}

void Countingsort( int list[], size_t elems, size_t low, size_t high )
{
	size_t capacity = high-low+1; // formula
	// calcula capacity
  int* aux = calloc( capacity, sizeof( int ) );
  // crea el arreglo auxiliar para enteros y lo inicializa a ceros.

	for (size_t i = 0; i < elems; i++) {
		g_contador++;
		int index = list[i];
		++aux[index];
	}
	int index = 0; // sacamos el indice para no regresar a cero cada ronda
	for(size_t i = 0; i < capacity; ++i){
		g_contador++;
		int reps = aux[i];
		for(int j = 0; j < reps; ++j){
			list[index] = i;
			++index;
		}
	}

 free( aux );
 // devuelve la memoria del arreglo auxiliar
}

#define NUM_ELEMS 9 // 5000

int main()
{
	int list[ NUM_ELEMS ] = { 1, 4, 4, 2, 7, 5, 2, 0, 9};
	//int list[NUM_ELEMS];

	//srand( time( NULL ) );

	//for (size_t i = 0; i < NUM_ELEMS; i++) {
		//list[i] =  (rand() % 20)+5;
	//}

	print( list , 8 , "  Antes: " );

	Countingsort( list, NUM_ELEMS, 0, 9 );
   // no existe ningún elemeno 0 en la lista, pero así es más fácil

	print( list , 8 , "Despues: " );

	printf("\ncomparaciones: %d\n", g_contador);
}
