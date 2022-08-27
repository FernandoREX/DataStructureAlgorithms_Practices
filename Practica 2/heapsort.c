// gcc -Wall -std=c99 -o a.out heapsort_para_terminar.c

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

size_t g_comparaciones = 0;

void print( int* list, short tam, char* msg )
{
	printf( "%s", msg );
	for( short i = 0; i < tam; ++i ){
		printf( "%d, ", list[ i ] );
	}
	printf( "\n" );
}

void swap( int* val1, int* val2 )
{
	int tmp = *val1;
	*val1 = *val2;
	*val2 = tmp;
}



void heapify( int list[], size_t n, size_t root )
{
	size_t left = (2*root) + 1;
	size_t right = (2*root) + 2;
	size_t largest = root;

	g_comparaciones++;
	if (left < n && list[left] > list[root])
		largest = left;

	g_comparaciones++;
	if (right < n && list[right] > list[largest])
		largest = right;

	if(largest != root){
		swap( &list[root] , &list[largest]);
		heapify( list , n , largest);
	}
}

void build_max_heap( int list[], short num_elems )
{
	for(size_t k = num_elems/2 ; k > 1 ; --k){
		heapify(list , num_elems , k-1);
	}
}

void HeapSort( int list[], short num_elems )
{
	build_max_heap( list , num_elems);
	print(list , 7 , " Max Heap: ");

	for (size_t i = num_elems; i > 1; i--) {
		swap( &list[0] , &list[i-1] );
		heapify(list , i-1 , 0);
	}
}

#define NUM_ELEMS 5000

int main()
{
	int list[NUM_ELEMS] = { 7, 6, 5, 4, 3, 2, 1 };
	
	srand( time( NULL ) );
	for(size_t i = 0; i < NUM_ELEMS; i++){
		list[i] = (rand() % 11) ;
	}

	print( list, 7 , "  Antes: " );
	g_comparaciones = 0;
	HeapSort( list, NUM_ELEMS );

	print( list, 7 , "Despues: " );

  printf( "Se realizaron %ld comparaciones.\n", g_comparaciones );

}
