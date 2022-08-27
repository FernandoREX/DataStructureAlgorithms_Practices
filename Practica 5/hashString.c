/*Copyright (C)
 * 2020 - francisco dot rodriguez at ingenieria dot unam dot mx
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
 #include <stdlib.h>
 #include <stdio.h>
 #include <stdbool.h>
 #include <assert.h>
 #include <time.h>
 #include <locale.h>
 #include <math.h>
 #include <string.h>
//          Esta versión sólo soporta llaves (keys) enteras positivas.

int g_colisiones = 0;
int g_bColisiones = 0;

enum{ EMPTY_CELL = -2, DELETED_CELL = -1 };

typedef struct
{
	char* table;    ///< Es la tabla hash
	int  size;     ///< Es el número máximo de elementos en la tabla
	int  len;      ///< Es el número actual de elementos en la tabla
} Map;

/**
 * @brief Crea una tabla Hash
 *
 * @param size El número de elementos para el arreglo subyacente
 *
 * @return Una referencia a un objeto del tipo Map
 */
Map* Create( int size )
{
   Map* m = malloc( sizeof( Map ) );
   if( m != NULL ){
      m->len = 0;
      m->size = size;
      m->table = malloc( m->size * sizeof( int ) );
      if( m->table == NULL ){
         free( m );
      } else{
         for( int i = 0; i < m->size; ++i ) m->table[ i ] = EMPTY_CELL;
         // inicializa todos los slots a "vacío"
      }
   }
   return m;
}

/**
 * @brief Destruye la tabla Hash
 *
 * @param map Referencia a un objeto Map
 */
void Destroy( Map* map )
{
   assert( map );

   free( map->table );
}

// Es la función hash
int h( char s[], int m )
{
	int i;
	for(i = 0 ; *s ; s++){
		i = 131 * i + (*s);
	}
  return i % m;
}

// es la función de resolución de colisiones
int probe( char* key, int i )
{
   return i + 1;
}

/**
 * @brief Inserta una llave (key) en la tabla Hash. En una aplicación del mundo
 * real se deberían guardar tanto la llave (key) como sus datos asociados
 * (value). En este ejemplo sólo se guarda la llave.
 *
 * @param map Referencia a un objeto Map
 * @param key La llave asociada a los datos. En este ejemplo LA LLAVE DEBE SER
 * ENTERA POSITIVA, INCLUYENDO EL CERO
 *
 * @return true si el valor (la llave en este ejemplo) se insertó en la tabla
 * hash; false en caso de estar duplicada la llave.
 */
bool Insert( Map* map, char* key )
{
   assert( map );
   assert( map->len < map->size );

   int pos;
   int home = pos = h( key, map->size );
   printf( "Calculé el valor hash: %d para la llave: %s\n", pos, key );

   int i = 0;

   while( map->table[ pos ] >= 0 ){
   // si el slot está ocupado, entonces tiene el valor de alguna llave,
   // y éstas son enteras positivas

      pos = ( home + probe( key, i ) ) % map->size;
      printf( "  Recalculé el valor hash: %d para la llave: %s\n", pos, key );

      if( map->table[ pos ] == key ) return false;
      // no se aceptan duplicados

      ++i;
			++g_colisiones;
   }

   map->table[ pos ] = key;
   ++map->len;

   return true;
}

/**
 * @brief Devuelve el valor asociado a key. En este ejemplo se devuelve el mismo
 *        valor de key en caso de encontrarse en la tabla.
 *
 * @param map Referencia a un objeto Map
 * @param key La llave asociada a los datos que se están buscando
 *
 * @return el mismo valor key en caso de encontrarse en la tabla. -1 en caso
 *         contrario.
 */

int Search( Map* map, char* key ){
  assert( map );
  assert( map->len > 0 );

 	int home = h( key, map->size );
 	int pos = home;

  printf( "Calculé el valor hash: %d para la llave: %s\n", pos, key );

  int i = 0;

	int slotsDeleted = 0; // variable local para cada celda borrada

  while( map->table[ pos ] != EMPTY_CELL && map->table[ pos ] != key ){

		if( map->table[pos] == DELETED_CELL)
			slotsDeleted++; // se incrementa la variable local

  	pos = ( home + probe( key, i ) ) % map->size;
  	printf( "  Recalculé el valor hash: %d para la llave: %s\n", pos, key );

  	++i;

		++g_bColisiones;
  }

	printf("\nSlots borrados y visitados: %d para la llave %s\n", slotsDeleted , key);

  if( map->table[ pos ] == key ){

  	return map->table[ pos ];
    // en una aplicación del mundo real debería devolver los datos (value)
    // asociados a la llave (key), pero en este ejemplo, el propio valor de
    // key es el "value"

  }else
  	return -1;
}

bool Remove( Map* map, char* key )
{
  assert( map );
  assert( map->len > 0 );

	int home = h( key, map->size );
  int pos = home;

  printf( "Calculé el valor hash: %d para la llave: %s\n", pos, key );

  int i = 0;

 	int slotsDeleted = 0; // variable local para cada celda borrada

  while( map->table[ pos ] != EMPTY_CELL && map->table[ pos ] != key ){

 		if( map->table[pos] == DELETED_CELL)
 			slotsDeleted++; // se incrementa la variable local

  	pos = ( home + probe( key, i ) ) % map->size;
   	printf( "  Recalculé el valor hash: %d para la llave: %s\n", pos, key );

  	++i;
  }

 	printf("\nSlots borrados y visitados: %d para la llave %s\n", slotsDeleted , key);

  if( map->table[ pos ] == key ){
		map->table[ pos ] = DELETED_CELL;
    map->len--;
   	return true;
     // en una aplicación del mundo real debería devolver los datos (value)
     // asociados a la llave (key), pero en este ejemplo, el propio valor de
     // key es el "value"
	}
  return false;
}

int Len(Map* map){
	return map->len;
}

float LoadFactor( Map* map){
	return ((float)map->len/map->size); // casting a float
}

#define TAM_TABLE 53 // numero primo

int main(){
	FILE *ranNames;
	ranNames = fopen("random_names.txt", "r");
	char names[80];
	char *str;

	Map* mapa = Create( TAM_TABLE );
  if( mapa == NULL ){
    printf( "Error creando la tabla hash.\n" );
    exit( 1 );
  }

	int i = 0;
	while( fgets( names, 80, ranNames ) != NULL ){
	 	if(Insert(mapa , names)){
			++i;
			printf("\nFactor de carga = %0.2f para el valor %s\n", LoadFactor(mapa) , names);
		}
 	}

	for(i = 0; i < 50; i++){
		if(Search(mapa , names) == names){
			printf("si se encontro la llave: %s\n", names);
		}else{
			printf("No se encontro la llave: %s\n", names);
		}
	}

	printf("El numero de colisiones para la busqueda fue: %d\n", g_bColisiones);

	printf("\nnumero de colisiones al insertar: %d\n", g_colisiones);


#if 0
  assert( Insert( mapa, 123 ) == true );
  assert( Insert( mapa, 170 ) == true );
  assert( Insert( mapa, 340 ) == true );
  assert( Insert( mapa, 510 ) == true );
  assert( Insert( mapa, 510 ) == false ); // duplicado

  assert( Search( mapa, 123 ) == 123 ); // sí está

  assert( Search( mapa, 100 ) == -1 ); // no está

  assert( Remove( mapa, 123 ) == true ); // no está implementada, va a fallar
#endif


  Destroy( mapa );
  mapa = NULL;
	fclose(ranNames);
	return 0 ;
}
