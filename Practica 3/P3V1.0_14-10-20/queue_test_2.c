
// para compilar:
// gcc -Wall -std=c99 -o prueba.out queue_test.c Queue.c DLL.c

#include <stdlib.h>
// para rand()

#include <time.h>
// para srand()

#include "Queue.h"

#define NUM_COLAS 5

int main()
{

	srand( time( NULL ) );
	
	Queue* muchasColas[ NUM_COLAS ];

	for( size_t i = 0; i < NUM_COLAS; ++i ){ muchasColas[ i ] = Queue_New(); }
	// creamos n colas

	for( size_t i = 0; i < NUM_COLAS; ++i ){

		size_t num_elems = rand() % 50 + 1;
		// llenamos cada cola desde 1 hasta 50 valores

		for( size_t j = 0; j < num_elems; ++j ){
			Queue_Enqueue( muchasColas[ i ], rand() % 1000 );
		}
		printf( "La cola %ld tiene %ld elementos.\n", i, Queue_Len( muchasColas[ i ] ) );
	}


	printf( "\n" );
	for( size_t i = 0; i < NUM_COLAS; ++i ){
		Item val;
		while( Queue_Dequeue( muchasColas[ i ], &val ) == true ){
			printf( "%d, ", val );
		}
		printf( "\n" );
	}


	for( size_t i = 0; i < NUM_COLAS; ++i ){ Queue_Delete( muchasColas[ i ] ); }
	// destruimos las n colas

}
