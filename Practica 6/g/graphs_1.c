//Comando para compilar: gcc -Wall -std=c99 -o g.out graphs_1.c
//Comando para ejecutar: g.out


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>


// 20/06/21:
// Esta versión no borra elementos
// Esta versión no modifica los datos originales

#define DBG_HELP 0

#if DBG_HELP == 1
#define DBG_PRINT( ... ) \
   do{\
      fprintf( stderr, "DBG:" __VA_ARGS__ ); \
   } while( 0 )
#else
#define DBG_PRINT( ... ) ;
#endif  

/**
 * @brief Es la información real.
 */
typedef struct 
{
   int val;   ///< campo de indexado (key) para los vértices
   char name; ///< una letra (por el momento)
} Data;


//----------------------------------------------------------------------
// Vertex stuff: 
//----------------------------------------------------------------------

/**
 * @brief Colores para el algoritmo BFS
 */
typedef enum
{
   BLACK, ///< vértice no descubierto
   GRAY,  ///< vértice descubierto
   WHITE, ///< vértice visitado
} eGraphColors;


/**
 * @brief Declara lo que es un nodo (lo usa la clase Vertex).
 */
typedef struct Node_
{
   size_t index;       ///< índice del elemento en la lista de vértices
   struct Node_ *next; ///< índice al nodo siguiente en la lista simplemente enlazada
} Node;

/**
 * @brief Mantiene juntas la llave (que se usa a lo largo de todas las funciones
 * de los grafos) y el índice de la misma en la tabla de datos.
 */
typedef struct
{
   int key;      ///< campo de indexado. En este ejemplo Data.val
   size_t value; ///< índice del elemento en la tabla de datos
} Pair;

/**
 * @brief Declara lo que es un vértice.
 */
typedef struct
{
   Pair  kv;        ///< Par <key, value>: <Data.val, index (a la tabla de datos)>
   Node* neighbors; ///< apunta al primer vecino, ¡no debe perderse!
   Node* cursor;    ///< Nodo de movimiento libre (freewheel pointer)


   eGraphColors color;
   int distance;
   /** Predecesor de este vértice.
   *
   * Este atributo es un índice, por lo que debería ser de tipo size_t; sin
   * embargo, dado que debemos inicializarlos a un estado "sin predecesor",
   * entonces necesitamos de un valor centinela, el cual es -1.
   */
   int predecessor;


} Vertex;

/**
 * @brief Devuelve el índice del vecino (correspondiente a la lista de vértices) al 
 * que apunta el |cursor| en la lista de vecinos.
 *
 * @param v El vértice base (del cual queremos conocer el índice de su vecino).
 *
 * @return El índice del vecino en la lista de vértices.
 *
 * @pre El cursor debe apuntar a un nodo válido en la lista de vecinos.
 *
 * Ejemplo
 * @code
   Vertex* v = Graph_GetVertexByKey( grafo, 100 );

   for( Vertex_Start( v ); !Vertex_End( v ); Vertex_Next( v ) )
   {
      size_t index = Vertex_Get( v );

      printf( "[Index=%ld, [Val=%d, Name=%c] ], ", 
         index, 
         data[ index ].val,
         data[ index ].name );
   }
   @endcode

   @note Esta función debe utilizarse únicamente cuando se recorra el grafo con las funciones Vertex_Start(), Vertex_End() y Vertex_Next().
 */
size_t Vertex_Get( const Vertex* v )
{
   assert( v->cursor );

   return v->cursor->index;
}

/**
 * @brief Hace que cursor libre apunte al inicio de la lista de vecinos. Se debe
 * de llamar siempre que se vaya a iniciar un recorrido de dicha lista.
 *
 * @param v El vértice de trabajo (es decir, el vértice del cual queremos obtener 
 * la lista de vecinos).
 */
void Vertex_Start( Vertex* v )
{
   assert( v );

   v->cursor = v->neighbors;
}

/**
 * @brief Mueve al cursor libre un nodo adelante.
 *
 * @param v El vértice de trabajo.
 *
 * @pre El cursor apunta a un nodo válido.
 * @post El cursor se movió un elemento a la derecha en la lista de vecinos.
 */
void Vertex_Next( Vertex* v )
{
   assert( v->cursor );

   v->cursor = v->cursor->next;
}

/**
 * @brief Indica si se alcanzó el final de la lista de vecinos.
 *
 * @param v El vértice de trabajo.
 *
 * @return true si se alcanazó el final de la lista; false en cualquier otro
 * caso.
 */
bool Vertex_End( const Vertex* v )
{
   return v->cursor == NULL;
}

void Vertex_SetColor( Vertex* v, eGraphColors color )
{
   assert( color == BLACK || color == GRAY || color == WHITE );

   v->color = color;
}

eGraphColors Vertex_GetColor( Vertex* v )
{
    return v->color;
}

void Vertex_SetDistance( Vertex* v, int distance )
{
    v->distance = distance;
}

int Vertex_GetDistance( Vertex* v )
{
    return v->distance;
}

// v El vertice de trabajo
// idx El indice(en la lista de vertices) predesesor 

void Vertex_SetPredecessor( Vertex* v, int predecessor_idx )
{
    v->predecessor = predecessor_idx;
}

int Vertex_GetPredecessor( Vertex* v )
{
    return v->predecessor;
}



//----------------------------------------------------------------------
// Graph stuff: 
//----------------------------------------------------------------------

/** Tipo del grafo.
 */
typedef enum 
{ 
   UNDIRECTED, ///< grafo no dirigido
   DIRECTED    ///< grafo dirigido (digraph)
} eGraphType; 

/**
 * @brief Declara lo que es un grafo.
 */
typedef struct
{
   Vertex* vertices; ///< Lista de vértices
   size_t size;      ///< Tamaño de la lista de vértices

   /**
    * Número de vértices actualmente en el grafo. 
    * Como esta versión no borra vértices, lo podemos usar como índice en la
    * función de inserción
    */
   size_t len;  

   eGraphType type; ///< tipo del grafo, UNDIRECTED o DIRECTED
} Graph;

/**
 * @brief Crea un nuevo grafo.
 *
 * @param size Número de vértices que tendrá el grafo. Este valor no se puede
 * cambiar luego de haberlo creado.
 *
 * @return Un nuevo grafo.
 *
 * @pre El número de elementos es mayor que 0.
 */
Graph* Graph_New( size_t size, eGraphType type )
{
   assert( size > 0 );

   Graph* g = (Graph*) malloc( sizeof( Graph ) );
   if( g ){
      g->size = size;
      g->len = 0;
      g->type = type;

      g->vertices = (Vertex*) calloc( size, sizeof( Vertex ) );
      // crea un arreglo para guardar los vértices


      // La siguiente inicialización NO ES NECESARIA, dado que calloc() ya se
      // encargó de eso; lo hice por si alguno de los campos debe ser puesto a
      // un valor diferente de cero:
      if( g->vertices ){
         
         Vertex* vertices = g->vertices;
         // para simplificar la notación. 
         // La variable |vertices| sólo existe dentro de este if.

         for( size_t i = 0; i < g->size; ++i ){
            vertices[ i ].kv.key = 0;
            vertices[ i ].kv.value = 0;
            vertices[ i ].neighbors = NULL;
         }
      } 

      // error de memoria para g->vertices:
      else{ 
         free( g );
         g = NULL;
      }
   }

   return g;
   // el cliente es responsable de verificar que el grafo se creó correctamente
}

void Graph_Delete( Graph** g )
{
   assert( *g );

   Graph* graph = *g;
   // para simplificar la notación 

   // 1. Borramos la verticesa enlazada de cada vértice:
   for( size_t i = 0; i < graph->size; ++i ){

      Vertex* vertex = &graph->vertices[ i ];
      // para simplificar la notación. 
      // La variable |vertex| sólo existe dentro de este for.

      Node* node = vertex->neighbors;
      while( node ){
         Node* tmp = node->next;
         free( node );
         node = tmp;
      }
   }

   // 2. Borramos el arreglo dinámico de vértices:
   free( graph->vertices );

   // 3. Borramos al objeto grafo:
   free( graph );

   // 4. Hacemos que el grafo apunte a nada (para control de daños):
   *g = NULL;
}

/**
 * @brief Imprime un reporte del grafo
 *
 * @param g     El grafo.
 * @param depth Cuán detallado deberá ser el reporte (0: lo mínimo)
 */
void Graph_Print( Graph* g, int depth )
{
   for( size_t i = 0; i < g->len; ++i ){

      Vertex* vertex = &g->vertices[ i ];
      // para simplificar la notación. 

      printf( "\n=== Vertex[ %ld ] ===\n", i );
      printf( "<%d, %ld>\n", vertex->kv.key, vertex->kv.value );

      // LEVEL 0:
      printf( vertex->neighbors ? "Has neighbors\n" : "Has no neighbors\n" );

      // LEVEL 1:
      if( depth > 0 ){

         for( Node* node = vertex->neighbors; node != NULL; node = node->next ){

            DBG_PRINT( "Print():(Node:%p, (*Node.index:%ld, *Node.next:%p))\n", node, node->index, node->next );
            
            printf( " %d ", g->vertices[ node->index ].kv.key );

            // LEVEL 2:
            if( depth > 1 ){
               printf( "(Node:%p)", node );
            }

            printf( "->" );
         }
         if( vertex->neighbors ) printf( " Nil\n" );
      }
   }
   printf( "\n" );
}

size_t Graph_GetLen(Graph* g)
{
    return g->len;
}

/**
 * @brief Crea un vértice a partir de los datos reales.
 *
 * @param g     El grafo.
 * @param val   Es el campo de indexado en los datos.
 * @param index Es el índice de los datos en la tabla de datos.
 */
void Graph_AddVertex( Graph* g, int val, size_t index )
{
   assert( g->len < g->size );

   Vertex* vertex = &g->vertices[ g->len ];
   // para simplificar la notación 

   vertex->kv.key     = val;
   vertex->kv.value   = index;
   vertex->neighbors = NULL;

   ++g->len;
}

size_t Graph_GetSize( Graph* g )
{
   return g->size;
}


// vertices: lista de vértices
// size: número de elementos en la lista de vértices
// key: valor a buscar
// ret: el índice donde está la primer coincidencia; -1 si no se encontró
static int find( Vertex* vertices, size_t size, int key )
{
   for( size_t i = 0; i < size; ++i ){

      if( vertices[ i ].kv.key == key ) return i;
   }

   return -1;
}

// busca si el índice (a la tabla de vértices) ya está en un vértice
static bool find_index_in_vertex( Vertex* vertex, int index )
{
   for( Node* node = vertex->neighbors; node != NULL; node = node->next ){
      if( node->index == index ) return true;
   }
   return false;
}

// vertex: vértice de trabajo
// index: índice en la lista de vértices del vértice vecino que está por insertarse
static void insert( Vertex* vertex, int index )
{
   if( find_index_in_vertex( vertex, index ) == false ){

   // Crea al nodo:
   Node* n = (Node*) calloc( 1, sizeof( Node ) );
   assert( n );
   DBG_PRINT( "Insert(): idx=%d, Node = %p\n", index, n );

   // Inserta al nodo al frente de la lista
   n->index = index;
   n->next = vertex->neighbors;
   vertex->neighbors = n;

   } 
   else DBG_PRINT( "insert: duplicated index\n" );
   
}



bool Graph_AddEdge( Graph* g, int start, int finish )
{
   assert( g->len > 0 );

   // obtenemos los índices correspondientes:
   int start_idx = find( g->vertices, g->size, start );
   int finish_idx = find( g->vertices, g->size, finish );

   DBG_PRINT( "AddEdge(): start_idx=%d, finish_idx=%d\n", start_idx, finish_idx );

   if( start_idx == -1 || finish_idx == -1 ) return false;
   // uno o ambos vértices no existen

   insert( &g->vertices[ start_idx ], finish_idx );
   // insertamos la arista start-finish

   if( g->type == UNDIRECTED ) insert( &g->vertices[ finish_idx ], start_idx );
   // si el grafo no es dirigido, entonces insertamos la arista finish-start

   return true;
}

/**
 * @brief Devuelve el nodo que apunta al inicio de la lista de vecinos.
 *
 * @param g     El grafo.
 * @param key   El criterio de búsqueda
 *
 * @return      El nodo que apunta a la lista de vecinos. Si no los tuviera,
 *              devuelve NULL
 */
Node* Graph_GetNeighborsByKey( Graph* g, int key )
{
   for( size_t i = 0; i < g->len; ++i ){

      if( g->vertices[ i ].kv.key == key ) return g->vertices[ i ].neighbors;
   }

   return NULL;
}

Vertex* Graph_GetVertexByKey( Graph* g, int key )
{
   assert( g );

   for( size_t i = 0; i < g->len; ++i ){

      if( g->vertices[ i ].kv.key == key ) return &g->vertices[ i ];
   }

   return NULL;
}

Vertex* Graph_GetVertexByIndex( Graph* g, size_t index )
{
   assert( g );
   assert( index < g->len );

   return &g->vertices[ index ];
}


/**
 * @brief Devuelve el índice en la lista de vértices del vértice indicado.
 *
 * @param g El grafo.
 * @param v El vértice del cual queremos obtener el índice.
 *
 * @return El índice en la lista de vértices del vértice v.
 *
 * @pre Ambos, el grafo y el vértice deben existir.
 */
size_t Graph_GetIndex( Graph* g, Vertex* v )
{
   assert( g );
   assert( v );

   size_t index;
   for( index = 0; index < g->len; ++index ){
      if( g->vertices[ index ].kv.key == v->kv.key ) break;
   }

   assert( index < g->len );

   return index;
}


//----------------------------------------------------------------------
// Queue stuff: 
//----------------------------------------------------------------------
typedef struct
{
   int*   array;
   size_t front;
   size_t back;
   size_t size;
   size_t len;
} Queue;

Queue* Queue_New( size_t size )
{
   assert( size > 0 );

   Queue* q = (Queue*) calloc( 1, sizeof( Queue ) );
   if( q ){

      q->size = size;
      q->array = (int*) calloc( size, sizeof( int ) );

      if( q->array == NULL ){
         free( q );
         q = NULL;
      }
   }

   return q;
}

void Queue_Delete( Queue** q )
{
   assert( *q );

   free( (*q)->array );
   free( *q );
   *q = NULL;
}

void Queue_Enqueue( Queue* q, int item )
{
   assert( q->len < q->size );
   q->array[q->back] = item;
   q->len++;
   q->back++;
   q->back = q->back % q->size;
}

int Queue_Dequeue( Queue* q )
{
   assert( q->len > 0 );
   int tmp = q->array[q->front];
   q->len--;
   q->front++;
   q->front = q->front % q->size;

   return tmp;
}

bool Queue_IsEmtpy( Queue* q )
{
    return q->front == 0 && q->back == 0;
}

//----------------------------------------------------------------------
//Print Back
//----------------------------------------------------------------------

void bfs_print_back(Graph* g, Queue* q, int tam)
{
    printf("PROCESSING VERTEXS...\n\n");
    int des;
    int res = 0;
    while (res < tam)
    {
        if (g->vertices[des].color == WHITE)
        {
            des = Queue_Dequeue(q);
            printf("---Vertex [%ld]---\n  Key: < %ld > \n\n", des, g->vertices[des].kv.key);
            res++;
        }
        
    }
}

//----------------------------------------------------------------------
// BFS algorithm 
//----------------------------------------------------------------------
void bfs(Graph* g, Vertex* start, Queue* out)
{
    for (size_t i = 0; i < g->len; i++)
    {
        Vertex* vertex = Graph_GetVertexByIndex(g, i);

        Vertex_SetColor(vertex, BLACK);
        //Vertice no descubierto

        Vertex_SetDistance(vertex, 0);
        //ponemos una distancia del vertice
        Vertex_SetPredecessor(vertex, -1);
    }
    Vertex_SetColor(start, GRAY); //Marcamos a star como descubierto

    //creamos una cola
    Queue* q = Queue_New(Graph_GetLen(g));
    assert(q);

    int tam = 0;

    //encolamos 
    Queue_Enqueue(q, Graph_GetIndex(g, start));

    while (!Queue_IsEmtpy(q))
    {
        size_t V_idx = Queue_Dequeue(q);

        //print back
        Queue_Enqueue(out, V_idx);

        tam++;

        Vertex* v = Graph_GetVertexByIndex(g, V_idx);  //v es el vertice del cual queremos vicitar los vecinos

        for (Vertex_Start(v); !Vertex_End(v); Vertex_Next(v))
        {
            size_t idx = Vertex_Get(v);
            Vertex* w = Graph_GetVertexByIndex(g, idx);

            if (Vertex_GetColor(w) == BLACK)
            {
                Vertex_SetColor(w, GRAY);
                //Vertice descubierto

                Vertex_SetDistance(w, (Vertex_GetDistance(v) + 1));
                //ponemos una distancia del vertice

                Vertex_SetPredecessor(w, Vertex_GetPredecessor(v));

                //encolamos 
                Queue_Enqueue(q, Graph_GetIndex(g, w));
            }

        }

        Vertex_SetColor(v, WHITE);

    }

    bfs_print_back(g, out, tam);

    Queue_Delete(&q);

}


//----------------------------------------------------------------------
// Driver program 
//----------------------------------------------------------------------
#define MAX_DATA 6

int main()
{
   // Inicializa la tabla de datos. <100,A>, <200,B>, ...
   Data data[ MAX_DATA ];
   char name = 'A';
   for( size_t i = 1; i <= MAX_DATA; ++i, ++name) {
      data[i-1].val = i * 100;
      data[i-1].name = name;
   }

   Graph* grafo = Graph_New( MAX_DATA, UNDIRECTED );

   for( size_t i = 0; i < MAX_DATA; ++i ) {
      
      Graph_AddVertex( 
         grafo,         // el grafo de trabajo
         data[ i ].val, // el campo de indexado en los datos
         i );           // índice de los datos en la tabla de datos
   }

   assert( Graph_AddEdge( grafo, 100, 200) == true );
   assert( Graph_AddEdge( grafo, 100, 300) == true );
   assert( Graph_AddEdge( grafo, 100, 400) == true );

   assert( Graph_AddEdge( grafo, 200, 100) == true );
   assert( Graph_AddEdge( grafo, 200, 500) == true );
   assert( Graph_AddEdge( grafo, 200, 600) == true );

   assert( Graph_AddEdge( grafo, 300, 100) == true );
   assert( Graph_AddEdge( grafo, 300, 400) == true );

   assert( Graph_AddEdge( grafo, 400, 100) == true );
   assert( Graph_AddEdge( grafo, 400, 300) == true );
   assert( Graph_AddEdge( grafo, 400, 500) == true );

   assert( Graph_AddEdge( grafo, 500, 200) == true );
   assert( Graph_AddEdge( grafo, 500, 400) == true );

   assert( Graph_AddEdge( grafo, 600, 200) == true );


   Graph_Print( grafo, 1 );


   printf( "100's neighbors: " );
   Vertex* v = Graph_GetVertexByKey( grafo, 100 );

   for( Vertex_Start( v ); !Vertex_End( v ); Vertex_Next( v ) ){

      size_t index = Vertex_Get( v );

      printf( "[Index=%ld, [Val=%d, Name=%c] ], ", 
         index, 
         data[ index ].val,
         data[ index ].name );
   }
   printf( "\n" );

   //creamos una cola para print back
   Queue* q_out = Queue_New(Graph_GetLen(grafo));
   assert(q_out);
   
   bfs( grafo, Graph_GetVertexByKey( grafo, 100), q_out);


   Queue_Delete(&q_out);
   Graph_Delete( &grafo );
   assert( grafo == NULL );
}
