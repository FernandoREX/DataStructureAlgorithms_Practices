
/* Quicksort para terminar */

#include <stdlib.h>
#include <stdio.h>

size_t g_comparaciones = 0;

void Print( int* list, size_t tam, char* msg )
{
	printf( "%s", msg );
	for( size_t i = 0; i < tam; ++i ){
		printf( "%d, ", list[ i ] );
	}
	printf( "\n" );
}

void Swap( int* val1, int* val2 )
{
}


void QuickSort( int list[], size_t first, size_t last )
{
}


#define NUM_ELEMS 10

int main()
{
	int list[ NUM_ELEMS ] = { 1, 8, 4, 9, 6, 3, 5, 2, 7, 0 };

	print( list, NUM_ELEMS, "Antes: " );

	QuickSort( list, 0, NUM_ELEMS - 1 );

	print( list, NUM_ELEMS, "Después: " );

}

