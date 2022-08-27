
// para compilar:
// gcc -Wall -std=c99 -o prueba.out queue_test.c Queue.c DLL.c

#include "Queue.h"

#define NUM_COLAS 5

int main()
{
	Queue* unaCola = Queue_New();

	printf( "Elementos en la cola: %ld\n", Queue_Len( unaCola ) );

	for( size_t i = 0; i < 20; ++i ){ Queue_Enqueue( unaCola, i + 100 ); }
	printf( "Elementos en la cola: %ld\n", Queue_Len( unaCola ) );

	while( Queue_IsEmpty( unaCola ) == false ){
		Item val;
		Queue_Dequeue( unaCola, &val );
		printf( "%d, ", val );
	}
	printf( "\n" );

	printf( "Elementos en la cola: %ld\n", Queue_Len( unaCola ) );

	Queue_Delete( unaCola );
}
