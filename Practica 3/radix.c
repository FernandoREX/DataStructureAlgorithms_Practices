/*Copyright (C) 
 * 2019 - eda1 dot fiunam at yahoo dot com dot mx
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 * 
 */

// Radixsort para terminar, 2021-1

// 1.- Cambia el nombre del archivo a radix.c
// 2.- Compila con:
//     gcc -Wall -std=c99 -osalida.out radix.c -lm Queue.c DLL.c


#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>
// bool, true, false

#include <iso646.h>
// and, or, not

#include <math.h>
// para pow()

#include "Queue.h"
// para usar la cola

void print( int list[], size_t tam, char msg[] )
{
	printf( "%s", msg );
	for( size_t i = 0; i < tam; ++i ){
		printf( "%d, ", list[ i ] );
	}
	printf( "\n" );
}

static size_t subKey( int val, size_t num_pos, size_t radix )
{

}

static void collect( int list[], Queue* queues[], size_t radix )
{

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

#define NUM_ELEMS 7

int main()
{
	int list[ NUM_ELEMS ] = { 630, 421, 527, 911, 912, 266, 85 };

	print( list, NUM_ELEMS, "  Antes: " );

	Radixsort10( list, NUM_ELEMS );

	print( list, NUM_ELEMS, "Después: " );
}
