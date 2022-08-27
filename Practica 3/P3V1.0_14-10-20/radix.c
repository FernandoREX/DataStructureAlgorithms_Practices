#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iso646.h>
#include <math.h>
#include "Queue.h"

int g_comparaciones = 0;

void print( int* list, size_t tam, char* msg )
{
	printf( "\n%s [ ", msg );
	for( size_t i = 0; i < tam; ++i ){
		if(i == tam-1)
			printf("%d ]", list[i] );
		else
			printf( "%d, ", list[ i ] );
	}
	printf( "\n" );
}

static size_t subKey( int val, size_t pos, size_t radix )
{
	int div = pow(10 , pos );
	return ((val/div) % radix);
}

static void collect( int list[], Queue* queues[], size_t radix )
{
	size_t index = 0;
	for (size_t i = 0; i < radix; ++i) {
		while(not Queue_IsEmpty(queues[i])){
			g_comparaciones++;
			int val;
			Queue_Dequeue( queues[i] , &val);
			list[index] = val;
			++index;
		}
	}
}

void Radixsort( int list[] , size_t elems , size_t num_pos , size_t radix)
{
	Queue* queues[ radix ];
   // crea un arreglo de colas

	for( size_t i = 0; i < radix; ++i ){ queues[ i ] = Queue_New(); }
   // crea cada una de las colas

	for(size_t i = 0; i < num_pos;++i){
		for (size_t j = 0; j < elems; ++j) {
			size_t whichQ = subKey(list[j], i , radix); // variable local del for
			Queue_Enqueue(queues[whichQ] , list[j]);
		}
		collect(list, queues, radix); // recoleccion posterior
		g_comparaciones++;
	}


	for( size_t i = 0; i < radix; ++i ){ Queue_Delete( queues[ i ] ); }
   // devuelve la memoria de las colas
}


void Radixsort10( int list[], size_t elems )
{
	size_t radix = 10;

	Queue* queues[ radix ];
   // crea un arreglo de colas

	for( size_t i = 0; i < radix; ++i ){ queues[ i ] = Queue_New(); }
   // crea cada una de las colas


	for( size_t i = 0; i < radix; ++i ){ Queue_Delete( queues[ i ] ); }
   // devuelve la memoria de las colas
}

#define NUM_ELEMS 5000

int main()
{
	//int list[ NUM_ELEMS ] = { 630, 421, 527, 911, 912, 266, 85 };
	int list[NUM_ELEMS];

	srand( time( NULL ) );

	for (size_t i = 0; i < NUM_ELEMS; i++) {
		list[i] =  (rand() % 4000);
	}

	print( list, 50, "  Antes: " );

	//Radixsort10( list, NUM_ELEMS );

	Radixsort( list, NUM_ELEMS , 4 , 4000); // num_pos es el tamaño del numero
																				// uni, dec, cen

	print( list, 50, "Despues: " );

	printf("\ncomparaciones: %d\n", g_comparaciones);
}
